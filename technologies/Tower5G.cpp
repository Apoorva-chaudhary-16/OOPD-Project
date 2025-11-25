#include "Tower5G.h"
#include "../basicIO.h"

void Tower5G::simulate() {
    io.outputstring("\n========================================\n");
    io.outputstring("     5G NETWORK SIMULATION\n");
    io.outputstring("========================================\n\n");

    io.outputstring("=== Network Information ===\n");
    io.outputstring("Technology: 5G (1800 MHz block)\n");
    io.outputstring("Total Bandwidth: 10000 kHz (10 MHz)\n");
    io.outputstring("Channel Bandwidth: 1000 kHz\n");

    long channels = numChannels();
    io.outputstring("Total Channels (1 MHz each): ");
    io.outputint((int)channels);
    io.outputstring("\nUsers per 1 MHz (base): ");
    io.outputint(users_per_channel);
    io.outputstring("\nAntennas (massive MIMO): ");
    io.outputint(antennas);
    io.outputstring("\n");

    long wirelessLimit = channels * users_per_channel * antennas;
    io.outputstring("Maximum Users (wireless limit): ");
    io.outputint((int)wirelessLimit);
    io.outputstring("\n");
}
