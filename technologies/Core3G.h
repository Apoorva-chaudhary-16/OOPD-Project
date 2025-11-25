#pragma once
#include "../CellularCore.h"

class Core3G : public CellularCore {
public:
    Core3G(int id = 0) : CellularCore(id) {}
    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 1000) + 1;
    }
};
