#pragma once
#include "technologies/NetworkTower.h"

/**
 * Tower5G
 * -------
 * 5G uses:
 *   - Higher frequencies (1800 MHz block)
 *   - Additional 10 MHz = 10,000 kHz
 *   - 30 users per 1 MHz
 *   - Channel width simulated as 1000 kHz
 *   - Massive MIMO = 16 antennas
 *   - 10 messages per user
 *
 * Must compute number of cellular cores.
 */

class Tower5G : public NetworkTower {
public:
    Tower5G(basicIO& io)
        : NetworkTower(io, "5G (1800 MHz)", 10000, 1000, 30, 10, 16) {}

    virtual void simulate() override {
        NetworkTower::simulate();

        long total_messages = calculateTotalMessages();

        const long MESSAGES_PER_CORE = 100000;
        long num_cores = (total_messages + MESSAGES_PER_CORE - 1) / MESSAGES_PER_CORE;

        io.outputstring("Number of cellular cores required: ");
        io.outputint((int)num_cores);
        io.outputstring("\n");
    }

private:
    long calculateTotalMessages() {
        long num_channels =
            (channel_width_khz == 0) ? 0 : (total_spectrum_khz / channel_width_khz);

        long max_users = num_channels * users_per_channel * antennas;

        return max_users * messages_per_user;
    }
};
