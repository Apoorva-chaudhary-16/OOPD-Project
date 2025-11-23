#pragma once
#include "CellularCore.h"

/**
 * Core2G
 * ------
 * Assumption for this project:
 * Core limit = (total_messages / 1000) + 1
 * This is a simplified constraint model for overhead handling.
 */

class Core2G : public CellularCore {
public:
    Core2G(int id = 0) : CellularCore(id) {
        overhead_per_100_msgs = 0;  // not used, but kept for uniformity
    }

    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 1000) + 1;
    }
};
