#pragma once
#include "../CellularCore.h"

class Core2G : public CellularCore {
public:
    Core2G(int id = 0) : CellularCore(id) {}
    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 1000) + 1;
    }
};
