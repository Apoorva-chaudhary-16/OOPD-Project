#pragma once
#include "CellularCore.h"

/**
 * Core3G
 * ------
 * Simplified model:
 * Core limit = (total_messages / 1000) + 1
 * Same model as 2G for consistency unless specified otherwise.
 */

class Core3G : public CellularCore {
public:
    Core3G(int id = 0) : CellularCore(id) {
        overhead_per_100_msgs = 0;
    }

    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 1000) + 1;
    }
};
