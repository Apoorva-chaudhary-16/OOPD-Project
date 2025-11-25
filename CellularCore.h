#pragma once

class CellularCore {
protected:
    int core_id;
    long overhead_per_100_msgs;
public:
    CellularCore(int id = 0) : core_id(id), overhead_per_100_msgs(0) {}
    virtual ~CellularCore() {}
    virtual long getCoreLimit(long total_messages) const = 0;
};
