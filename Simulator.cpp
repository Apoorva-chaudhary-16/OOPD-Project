#include "Simulator.h"
#include "basicIO.h"
#include "Exceptions.h"
#include "technologies/Tower2G.h"
#include "technologies/Tower3G.h"
#include "technologies/Tower4G.h"
#include "technologies/Tower5G.h"

// Syscall prototypes (from syscall.S)
extern "C" long syscall3(long number, long arg1, long arg2, long arg3);
extern "C" long syscall6(long number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

// Simple file reader using syscalls (no stdlib)
static long read_file_to_buffer(const char* path, char* outBuf, long maxLen) {
    if (!path || !outBuf || maxLen <= 0) return 0;

    long fd = syscall6(2, (long)path, 0, 0, 0, 0, 0); // open(path, O_RDONLY)
    if (fd < 0) return 0;

    long total = 0;
    while (total < maxLen - 1) {
        long toRead = (maxLen - 1 - total);
        if (toRead > 1024) toRead = 1024;
        long r = syscall3(0, fd, (long)(outBuf + total), toRead); // read
        if (r <= 0) break;
        total += r;
    }

    outBuf[total] = '\0';
    syscall3(3, fd, 0, 0); // close
    return total;
}

// Parse integers from buffer (whitespace, commas and newlines are separators)
static int parse_ints_from_buffer(const char* buf, int* outInts, int maxInts) {
    if (!buf || !outInts || maxInts <= 0) return 0;
    int count = 0;
    int i = 0;
    while (buf[i] && count < maxInts) {
        // skip non-digit / non-minus
        while (buf[i] && !( (buf[i] >= '0' && buf[i] <= '9') || buf[i] == '-' )) ++i;
        if (!buf[i]) break;

        int neg = 0;
        if (buf[i] == '-') { neg = 1; ++i; }

        long val = 0;
        int digits = 0;
        while (buf[i] >= '0' && buf[i] <= '9') {
            val = val * 10 + (buf[i] - '0');
            ++i;
            ++digits;
        }
        if (digits == 0) continue;
        if (neg) val = -val;
        outInts[count++] = (int)val;
    }
    return count;
}

// Assignment helper: assign users to channels with capacity
static int assign_users_to_channels(int channels, int capPerChannel,
                                    int totalRequestedUsers,
                                    int* requested, int reqCount,
                                    int* assigned, int* unassigned_out) {
    int i;
    for (i = 0; i < channels; ++i) assigned[i] = 0;

    int totalAssigned = 0;
    int overflowPool = 0;

    // First pass: per-channel request + overflow
    for (i = 0; i < channels; ++i) {
        int want = 0;
        if (i < reqCount) want = requested[i];
        want += overflowPool;
        overflowPool = 0;

        int place = want;
        if (place > capPerChannel) {
            assigned[i] = capPerChannel;
            overflowPool = place - capPerChannel;
        } else {
            assigned[i] = place;
        }
        totalAssigned += assigned[i];
    }

    int unassigned = overflowPool;

    // Now see if TOTAL_USERS > sum(requested), and try to stuff extras
    int sumRequested = 0;
    for (i = 0; i < reqCount && i < channels; ++i) sumRequested += requested[i];
    int extraFromTotal = 0;
    if (totalRequestedUsers > sumRequested) extraFromTotal = totalRequestedUsers - sumRequested;

    int extra = extraFromTotal;
    for (i = 0; i < channels && extra > 0; ++i) {
        int freeSlots = capPerChannel - assigned[i];
        if (freeSlots <= 0) continue;
        int put = (extra <= freeSlots) ? extra : freeSlots;
        assigned[i] += put;
        totalAssigned += put;
        extra -= put;
    }

    if (extra > 0) unassigned += extra;

    // Safety: never assign more than totalRequestedUsers
    if (totalAssigned > totalRequestedUsers) {
        int reduce = totalAssigned - totalRequestedUsers;
        for (i = channels - 1; i >= 0 && reduce > 0; --i) {
            int take = (assigned[i] <= reduce) ? assigned[i] : reduce;
            assigned[i] -= take;
            reduce -= take;
            totalAssigned -= take;
        }
        unassigned = 0;
    }

    if (unassigned_out) *unassigned_out = unassigned;
    return totalAssigned;
}

#define MAX_FILE_BYTES 65536
#define MAX_INTS 8192

Simulator::Simulator(basicIO& i) : io(i) {}

void Simulator::run() {
    int runAgain = 1;

    while (runAgain) {
        try {
            io.outputstring("========================================\n");
            io.outputstring("   CELLULAR NETWORK SIMULATOR\n");
            io.outputstring("========================================\n");
            io.outputstring("Select network to simulate:\n");
            io.outputstring("1. 2G\n2. 3G\n3. 4G\n4. 5G\n5. Exit\n");
            io.outputstring("Enter choice: ");
            int choice = io.inputint();

            if (choice == 5) return;

            NetworkTower* tower = 0;
            if (choice == 1) tower = new Tower2G(io);
            else if (choice == 2) tower = new Tower3G(io);
            else if (choice == 3) tower = new Tower4G(io);
            else if (choice == 4) tower = new Tower5G(io);
            else {
                throw ERROR_INVALID_INPUT;
            }

            tower->simulate();

            io.outputstring("\nEnter input filename (e.g. input.txt) containing TOTAL_USERS followed by per-channel desired users: ");
            char filename[256];
            io.inputstring(filename, 256);

            static char filebuf[MAX_FILE_BYTES];
            long bytes = read_file_to_buffer(filename, filebuf, MAX_FILE_BYTES);
            if (bytes <= 0) {
                delete tower;
                throw ERROR_INVALID_INPUT;  // bad/missing file
            }

            static int ints[MAX_INTS];
            int intCount = parse_ints_from_buffer(filebuf, ints, MAX_INTS);
            if (intCount < 2) {
                delete tower;
                throw ERROR_INVALID_INPUT;  // need TOTAL_USERS + at least one channel
            }

            int totalUsersFromFile = ints[0];
            if (totalUsersFromFile <= 0) {
                delete tower;
                throw ERROR_INVALID_INPUT;  // total users must be positive
            }

            io.outputstring("\nEnter core overhead percentage (0-100): ");
            int overheadPercent = io.inputint();
            // strict: if invalid, throw error instead of clamping
            if (overheadPercent < 0 || overheadPercent > 100) {
                delete tower;
                throw ERROR_INVALID_INPUT;
            }

            io.outputstring("Enter maximum messages that ONE core can handle: ");
            int coreCapacity = io.inputint();
            if (coreCapacity <= 0) {
                delete tower;
                throw ERROR_CORE_LIMIT;
            }

            long channelsLong = tower->numChannels();
            int channels = (int)channelsLong;
            int usersPerChannel = tower->getUsersPerChannel();
            int antennas = tower->getAntennas();
            int messagesPerUser = tower->getMessagesPerUser();
            int capPerChannel = usersPerChannel * antennas;
            long wirelessLimit = channelsLong * (long)capPerChannel;

            int perChannelCount = intCount - 1;
            if (perChannelCount < channels) {
                delete tower;
                throw ERROR_INVALID_INPUT;  // missing per-channel entries
            }

            // copy per-channel requested values with validation
            static int requestedArr[1024];
            int reqCount = perChannelCount;
            if (reqCount > 1024) reqCount = 1024;

            int i;
            for (i = 0; i < reqCount; ++i) {
                int val = ints[i + 1];
                if (val < 0) {
                    delete tower;
                    throw ERROR_INVALID_INPUT;  // negative users NOT allowed
                }
                if (val > capPerChannel) {
                    delete tower;
                    throw ERROR_OVER_CAPACITY; // requested more than per-channel capacity
                }
                requestedArr[i] = val;
            }

            int assignedArrCount = channels;
            int* assigned = new int[assignedArrCount];
            int unassigned = 0;

            int totalAssigned = assign_users_to_channels(channels, capPerChannel,
                                                         totalUsersFromFile,
                                                         requestedArr, reqCount,
                                                         assigned, &unassigned);

            long baseMessages = (long)messagesPerUser * (long)totalAssigned;
            long overheadMessages = (baseMessages * overheadPercent) / 100;
            long totalMessages = baseMessages + overheadMessages;

            long neededCores = (coreCapacity > 0) ? ((totalMessages + coreCapacity - 1) / coreCapacity) : 0;

            io.outputstring("\n--- Capacity Summary ---\n");
            io.outputstring("Wireless limit (tower): ");
            io.outputint((int)wirelessLimit);
            io.outputstring("\n");

            io.outputstring("Users requested in file (total): ");
            io.outputint(totalUsersFromFile);
            io.outputstring("\n");

            io.outputstring("Total users assigned (connected): ");
            io.outputint(totalAssigned);
            io.outputstring("\n");

            io.outputstring("Unassigned users due to capacity/overflow: ");
            io.outputint(unassigned);
            io.outputstring("\n");

            io.outputstring("Number of cores required (given core capacity): ");
            io.outputint((int)neededCores);
            io.outputstring("\n");

            // --- Extra: Full potential cores for 4G/5G ---
            int is4G = (tower->getChannelWidthKhz() == 10 && tower->getTotalSpectrumKhz() == 1000);
            int is5G = (tower->getChannelWidthKhz() == 1000 && tower->getTotalSpectrumKhz() == 10000);

            if (is4G || is5G) {
                long fullUsers = wirelessLimit;
                long fullBase = (long)messagesPerUser * fullUsers;
                long fullOver = (fullBase * overheadPercent) / 100;
                long fullTotal = fullBase + fullOver;
                long fullCores = (coreCapacity > 0) ? ((fullTotal + coreCapacity - 1) / coreCapacity) : 0;

                io.outputstring("\n*** Full-Potential Core Usage ***\n");
                io.outputstring("If ALL possible users are connected (");
                io.outputint((int)fullUsers);
                io.outputstring(" users), cores required: ");
                io.outputint((int)fullCores);
                io.outputstring("\n");
            }

            io.outputstring("\n=== Channel Allocations ===\n");
            for (i = 0; i < channels; ++i) {
                io.outputstring("Channel ");
                io.outputint(i);
                io.outputstring(": ");
                io.outputint(assigned[i]);
                io.outputstring(" users assigned\n");
            }

            // First channel details + actual user IDs
            io.outputstring("\n=== First Channel (0) Details ===\n");
            io.outputstring("Requested for channel 0: ");
            int req0 = (perChannelCount > 0) ? requestedArr[0] : 0;
            io.outputint(req0);
            io.outputstring("\nAssigned in channel 0: ");
            io.outputint(assigned[0]);
            io.outputstring("\n");

            // User IDs in channel 0: assume users labeled from 1000 upward, sequential by assignment order
            io.outputstring("User IDs in channel 0:\n");
            int startId = 1000;
            int uid;
            for (uid = 0; uid < assigned[0]; ++uid) {
                io.outputstring("  User ");
                io.outputint(startId + uid);
                io.outputstring("\n");
            }

            io.outputstring("\n--- Message Statistics ---\n");
            io.outputstring("Messages per user: ");
            io.outputint(messagesPerUser);
            io.outputstring("\n");
            io.outputstring("Base messages (without overhead): ");
            io.outputint((int)baseMessages);
            io.outputstring("\n");
            io.outputstring("Overhead messages: ");
            io.outputint((int)overheadMessages);
            io.outputstring("\n");
            io.outputstring("Total messages: ");
            io.outputint((int)totalMessages);
            io.outputstring("\n");

            delete [] assigned;
            delete tower;

            io.outputstring("\nPress 1 to run another simulation, 0 to exit: ");
            runAgain = io.inputint();
            if (runAgain != 1) runAgain = 0;
        }
        catch (int err) {
            if (err == ERROR_INVALID_INPUT) {
                io.errorstring("Error: Invalid input (menu choice, file, or value).\n");
            } else if (err == ERROR_OVER_CAPACITY) {
                io.errorstring("Error: Requested users exceed per-channel capacity.\n");
            } else if (err == ERROR_CORE_LIMIT) {
                io.errorstring("Error: Invalid or zero core capacity.\n");
            } else {
                io.errorstring("Unknown error occurred.\n");
            }

            io.outputstring("\nSimulation aborted. Press 1 to try again, 0 to exit: ");
            runAgain = io.inputint();
            if (runAgain != 1) runAgain = 0;
        }
    }
}
