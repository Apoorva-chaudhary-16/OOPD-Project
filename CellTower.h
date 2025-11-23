#pragma once

#include "basicIO.h"
#include "Container.h"

/**
 * Abstract base class representing a cell tower.
 * 
 * Required OOP concepts:
 *  - Abstraction (pure virtual functions)
 *  - Inheritance (all 2G/3G/4G/5G towers inherit from this)
 *  - Data hiding (protected members)
 */

class CellTower {
protected:
    int tower_id;

    long total_spectrum_khz;   // e.g., 1000 kHz for 2G, 3G, 4G
    long channel_width_khz;    // e.g., 200 kHz for 2G/3G, 10 kHz for 4G, 1 MHz for 5G
    int users_per_channel;     // users per channel based on technology
    int antennas;              // MIMO support (1 for 2G/3G, 4 for 4G, 16 for 5G)

public:
    CellTower(int id = 0)
        : tower_id(id),
          total_spectrum_khz(0),
          channel_width_khz(0),
          users_per_channel(0),
          antennas(1) {}

    virtual ~CellTower() {}

    // ----- PURE VIRTUAL FUNCTIONS -----
    virtual long calculateMaxUsers() const = 0;
    virtual int usersInFirstChannel() const = 0;
    virtual void simulate() = 0;
};
