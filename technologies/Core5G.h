#pragma once
#include "CellularCore.h"

/**
 * Core5G
 * ------
 * Massive MIMO + high throughput.
 * Simplified model:
 *   Core limit = total_messages / 100000 + 1
 */

class Core5G : public CellularCore {
public:
    Core5G(int id = 0) : CellularCore(id) {
        overhead_per_100_msgs = 0;
    }

    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 100000) + 1;
    }
};
