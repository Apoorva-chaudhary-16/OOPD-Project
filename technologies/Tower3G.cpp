#include "Tower3G.h"
#include "../basicIO.h"

void Tower3G::simulate() {
    io.outputstring("\n========================================\n");
    io.outputstring("     3G NETWORK SIMULATION\n");
    io.outputstring("========================================\n\n");
    io.outputstring("=== Network Information ===\n");
    io.outputstring("Technology: 3G\n");
    io.outputstring("Total Bandwidth: 1000 kHz (1 MHz)\n");
    io.outputstring("Channel Bandwidth: 200 kHz\n");

    long channels = numChannels();
    io.outputstring("Total Channels: ");
    io.outputint((int)channels);
    io.outputstring(" (");
    io.outputint((int)channels);
    io.outputstring(" × 200 kHz)\n");

    io.outputstring("Users per Channel (CDMA): ");
    io.outputint(users_per_channel);
    io.outputstring("\n");

    long wirelessLimit = channels * users_per_channel * antennas;
    io.outputstring("Maximum Users (wireless limit): ");
    io.outputint((int)wirelessLimit);
    io.outputstring("\n");
}
