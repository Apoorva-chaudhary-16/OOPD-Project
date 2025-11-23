#pragma once

#include "basicIO.h"

/**
 * NetworkTower
 * ------------
 * Base class for all technology towers (2G, 3G, 4G, 5G)
 * This class provides:
 *   - Common attributes
 *   - Base calculate logic
 *   - Polymorphic simulate()
 */

class NetworkTower {
protected:
    basicIO& io;

    const char* name;            // Technology name
    long total_spectrum_khz;     // Total bandwidth
    long channel_width_khz;      // Channel width
    int users_per_channel;       // Capacity per channel
    int messages_per_user;       // Messages per user
    int antennas;                // MIMO factor

public:
    NetworkTower(
        basicIO& io,
        const char* n,
        long ts,                 // total spectrum
        long cw,                 // channel width
        int upc,                 // users per channel
        int mpu,                 // messages per user
        int ant                  // antenna factor
    )
    : io(io),
      name(n),
      total_spectrum_khz(ts),
      channel_width_khz(cw),
      users_per_channel(upc),
      messages_per_user(mpu),
      antennas(ant)
    {}

    virtual ~NetworkTower() {}

    // Base simulation common to all technologies
    virtual void simulate() {
        io.outputstring("--- Simulating ");
        io.outputstring(name);
        io.outputstring(" ---\n");

        long num_channels = (channel_width_khz == 0)
            ? 0
            : (total_spectrum_khz / channel_width_khz);

        long max_users = num_channels * users_per_channel * antennas;

        io.outputstring("Total users supported: ");
        io.outputint((int)max_users);
        io.outputstring("\n");

        int first_channel_users = users_per_channel * antennas;
        io.outputstring("Users in first channel: ");
        io.outputint(first_channel_users);
        io.outputstring("\n");
    }
};
