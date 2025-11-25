#include "Tower4G.h"
#include "../basicIO.h"

void Tower4G::simulate() {
    io.outputstring("\n========================================\n");
    io.outputstring("     4G NETWORK SIMULATION\n");
    io.outputstring("========================================\n\n");

    io.outputstring("=== Network Information ===\n");
    io.outputstring("Technology: 4G\n");
    io.outputstring("Total Bandwidth: 1000 kHz (1 MHz)\n");
    io.outputstring("Channel Bandwidth: 10 kHz\n");

    long channels = numChannels();
    io.outputstring("Total Subchannels: ");
    io.outputint((int)channels);
    io.outputstring("\nUsers per Subchannel: ");
    io.outputint(users_per_channel);
    io.outputstring("\nAntennas (MIMO): ");
    io.outputint(antennas);
    io.outputstring("\n");

    long wirelessLimit = channels * users_per_channel * antennas;
    io.outputstring("Maximum Users (wireless limit): ");
    io.outputint((int)wirelessLimit);
    io.outputstring("\n");
}
