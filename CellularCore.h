#pragma once

/**
 * Abstract base class representing the cellular core.
 * Each generation of core (2G/3G/4G/5G) inherits and overrides behavior.
 */

class CellularCore {
protected:
    int core_id;
    long overhead_per_100_msgs;  // overhead from problem statement

public:
    CellularCore(int id = 0)
        : core_id(id), overhead_per_100_msgs(0) {}

    virtual ~CellularCore() {}

    /**
     * Calculates how many cores are required to support (messages) load.
     * Must be implemented by each generation.
     */
    virtual long getCoreLimit(long total_messages) const = 0;
};
