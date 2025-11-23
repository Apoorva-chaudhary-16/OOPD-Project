#pragma once
#include "CellularCore.h"

/**
 * Core4G
 * ------
 * Simplified model:
 *   Core limit = total_messages / 100000 + 1
 * 
 * (Matches project requirement for 4G + OFDM + multiple antennas)
 */

class Core4G : public CellularCore {
public:
    Core4G(int id = 0) : CellularCore(id) {
        overhead_per_100_msgs = 0;
    }

    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 100000) + 1;
    }
};
