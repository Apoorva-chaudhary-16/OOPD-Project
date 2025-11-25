#pragma once
#include "../basicIO.h"

/**
 * NetworkTower base that provides common fields and a base simulate().
 * Derived tower classes override simulate() and may add compute details.
 *
 * Added simple getters so Simulator (which does file-driven allocation)
 * can obtain tower-specific parameters without using STL.
 */

class NetworkTower {
protected:
    basicIO& io;
    const char* name;
    long total_spectrum_khz;
    long channel_width_khz;
    int users_per_channel;
    int messages_per_user;
    int antennas;

public:
    NetworkTower(basicIO& io_ref, const char* n, long ts, long cw, int upc, int mpu, int ant)
        : io(io_ref),
          name(n),
          total_spectrum_khz(ts),
          channel_width_khz(cw),
          users_per_channel(upc),
          messages_per_user(mpu),
          antennas(ant) {}

    virtual ~NetworkTower() {}

    virtual void simulate() {
        io.outputstring("--- Simulating ");
        io.outputstring(name);
        io.outputstring(" ---\n");
    }

    // helper accessible to derived classes
    long numChannels() const {
        if (channel_width_khz == 0) return 0;
        return total_spectrum_khz / channel_width_khz;
    }

    // ===== GETTERS for Simulator (no STL) =====
    const char* getName() const { return name; }
    long getTotalSpectrumKhz() const { return total_spectrum_khz; }
    long getChannelWidthKhz() const { return channel_width_khz; }
    int getUsersPerChannel() const { return users_per_channel; }
    int getMessagesPerUser() const { return messages_per_user; }
    int getAntennas() const { return antennas; }
};
