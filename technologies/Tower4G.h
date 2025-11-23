#pragma once
#include "technologies/NetworkTower.h"

/**
 * Tower4G
 * -------
 * 4G uses OFDM with:
 *   - Total spectrum: 1000 kHz (1 MHz)
 *   - Channel width: 10 kHz (subcarriers)
 *   - 30 users per 10 kHz
 *   - 10 messages per user
 *   - up to 4 antennas (4× MIMO)
 * 
 * Must also compute number of cores needed.
 */

class Tower4G : public NetworkTower {
public:
    Tower4G(basicIO& io)
        : NetworkTower(io, "4G", 1000, 10, 30, 10, 4) {}

    virtual void simulate() override {
        NetworkTower::simulate();  // base class prints core results

        long total_messages = calculateTotalMessages();

        const long MESSAGES_PER_CORE = 100000;  // core capacity
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
