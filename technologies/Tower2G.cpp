#include "Tower2G.h"
#include "../basicIO.h"

// We'll implement simulation fully using no STL, printing with basicIO.

void Tower2G::simulate() {
    io.outputstring("\n========================================\n");
    io.outputstring("     2G NETWORK SIMULATION\n");
    io.outputstring("========================================\n\n");

    // network info
    io.outputstring("=== Network Information ===\n");
    io.outputstring("Technology: 2G\n");
    io.outputstring("Total Bandwidth: 1000 kHz (1 MHz)\n");
    io.outputstring("Channel Bandwidth: 200 kHz\n");

    long channels = numChannels();
    // print total channels line
    io.outputstring("Total Channels: ");
    io.outputint((int)channels);
    io.outputstring(" (");
    io.outputint((int)channels);
    io.outputstring(" × 200 kHz)\n");

    io.outputstring("Users per Channel (TDMA): ");
    io.outputint(users_per_channel);
    io.outputstring("\n");

    long wirelessLimit = channels * users_per_channel * antennas;
    io.outputstring("Maximum Users (wireless limit): ");
    io.outputint((int)wirelessLimit);
    io.outputstring("\n\n");

    // Tower info
    io.outputstring("Tower ID: 1\n");
    io.outputstring("Frequency Bands: ");
    io.outputint((int)channels);
    io.outputstring("\nSlots per Band: ");
    io.outputint(users_per_channel);
    io.outputstring("\nMax Capacity: ");
    io.outputint((int)wirelessLimit);
    io.outputstring("\nConnected Users: 0\n\n");
    // Note: actual allocation is handled by Simulator (file-driven)
}
