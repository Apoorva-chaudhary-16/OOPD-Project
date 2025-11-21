/*
 * main.cpp
 *
 * Cellular Network Simulator main file.
 * This file defines the required classes (UserDevice, CellularCore,
 * NetworkTechnology) and uses polymorphism to simulate 2G, 3G, 4G, and 5G
 * networks.
 *
 * It uses *only* the provided 'basicIO.h' for all input/output operations.
 *
 * This version uses C++ threads to run the simulations concurrently.
 * It uses a mutex to protect the global 'io' object from data races.
 */

#include "basicIO.h" // Use the provided I/O header

// C++ Standard Library headers for threading
#include <thread>
#include <mutex>
#include <vector>
#include <functional> // For std::ref

// --- Global Mutex ---
// We need a mutex to protect the global 'io' object.
// All threads will try to write to STDOUT via 'io',
// and this mutex prevents their output from being jumbled.
std::mutex io_mutex;


// --- Q1: Simulation Framework Classes ---
// (These class definitions are IDENTICAL to the previous answer)

/*
 * UserDevice
 */
class UserDevice {
public:
    int device_id;
    UserDevice(int id = 0) : device_id(id) {}
};

/*
 * CellularCore
 */
class CellularCore {
public:
    long core_id;
    CellularCore(long id = 0) : core_id(id) {}
};

/*
 * NetworkTechnology (Base Class)
 */
class NetworkTechnology {
protected:
    basicIO& io; // Reference to the global 'io' object
    const char* name;
    long total_spectrum_khz;
    long channel_width_khz;
    int users_per_channel;
    int messages_per_user;
    int antennas;

public:
    NetworkTechnology(basicIO& anIO, const char* n, long ts, long cw, int upc, int mpu, int a)
        : io(anIO), name(n), total_spectrum_khz(ts), channel_width_khz(cw), 
          users_per_channel(upc), messages_per_user(mpu), antennas(a) {}

    virtual ~NetworkTechnology() {}

    virtual long calculate_max_users() {
        if (channel_width_khz == 0) return 0;
        long num_channels = total_spectrum_khz / channel_width_khz;
        return num_channels * users_per_channel * antennas;
    }

    virtual long calculate_total_messages() {
        return calculate_max_users() * messages_per_user;
    }

    virtual void run_simulation() {
        io.outputstring("--- Simulating ");
        io.outputstring(name);
        io.outputstring(" ---\n");

        long max_users = calculate_max_users();
        io.outputstring("Total user devices supported: ");
        io.outputint((int)max_users);
        io.outputstring("\n");

        int first_channel_users = users_per_channel * antennas;
        io.outputstring("Users occupying the first channel: ");
        io.outputint(first_channel_users);
        io.outputstring("\n");
    }
};

// --- Q2: 2G Communication ---
class Tower2G : public NetworkTechnology {
public:
    Tower2G(basicIO& anIO) 
        : NetworkTechnology(anIO, "2G", 1000, 200, 16, 20, 1) {}
};

// --- Q3: 3G Communication ---
class Tower3G : public NetworkTechnology {
public:
    Tower3G(basicIO& anIO) 
        : NetworkTechnology(anIO, "3G", 1000, 200, 32, 10, 1) {}
};

// --- Q4: 4G Communication ---
class Tower4G : public NetworkTechnology {
public:
    Tower4G(basicIO& anIO) 
        : NetworkTechnology(anIO, "4G", 1000, 10, 30, 10, 4) {}

    virtual void run_simulation() override {
        NetworkTechnology::run_simulation();
        long total_messages = calculate_total_messages();
        const long MESSAGES_PER_CORE = 100000;
        long num_cores = (total_messages + MESSAGES_PER_CORE - 1) / MESSAGES_PER_CORE;
        io.outputstring("Number of cellular cores needed (at 100k msgs/core): ");
        io.outputint((int)num_cores);
        io.outputstring("\n");
    }
};

// --- Q5: 5G Communication ---
class Tower5G : public NetworkTechnology {
public:
    Tower5G(basicIO& anIO) 
        : NetworkTechnology(anIO, "5G (1800 MHz)", 10000, 1000, 30, 10, 16) {}

    virtual void run_simulation() override {
        NetworkTechnology::run_simulation();
        long total_messages = calculate_total_messages();
        const long MESSAGES_PER_CORE = 100000;
        long num_cores = (total_messages + MESSAGES_PER_CORE - 1) / MESSAGES_PER_CORE;
        io.outputstring("Number of cellular cores needed (at 100k msgs/core): ");
        io.outputint((int)num_cores);
        io.outputstring("\n");
    }
};


// --- Thread Task Function ---

/**
 * @brief A wrapper function that can be executed on a thread.
 * It locks the global mutex, runs the simulation for a single
 * technology, and then unlocks the mutex.
 *
 * @param sim A pointer to the NetworkTechnology object to simulate.
 */
void run_simulation_task(NetworkTechnology* sim) {
    // Lock the mutex. This ensures only one thread can
    // access the 'io' object at a time.
    std::lock_guard<std::mutex> lock(io_mutex);

    // Run the simulation. The output is now protected.
    sim->run_simulation();
}


// --- Main Simulation Framework ---

extern "C" int main() {
    // 'io' is the global basicIO object
    io.outputstring("===== Cellular Network Simulator (Concurrent) =====\n\n");

    // --- Instantiate the four simulation objects ---
    // We pass the global 'io' object to all of them.
    Tower2G sim2G(io);
    Tower3G sim3G(io);
    Tower4G sim4G(io);
    Tower5G sim5G(io);

    // --- Create a vector to hold our threads ---
    std::vector<std::thread> simulation_threads;

    io.outputstring("Launching all 4 simulations on concurrent threads...\n\n");

    // --- Launch Threads ---
    // We create one thread for each simulation task.
    // The 'run_simulation_task' function will be the entry point
    // for each thread.
    simulation_threads.push_back(std::thread(run_simulation_task, &sim2G));
    simulation_threads.push_back(std::thread(run_simulation_task, &sim3G));
    simulation_threads.push_back(std::thread(run_simulation_task, &sim4G));
    simulation_threads.push_back(std::thread(run_simulation_task, &sim5G));

    // --- Wait for Threads to Complete ---
    // We must 'join' all threads. This makes the 'main' thread
    // wait until all four simulations have finished.
    for (std::thread& t : simulation_threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    io.outputstring("\nAll simulations complete.\n");
    io.outputstring("===== Simulation Complete =====\n");
    
    return 0; 
}