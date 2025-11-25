#pragma once
#include "../CellularCore.h"
class Core4G : public CellularCore {
public:
    Core4G(int id = 0) : CellularCore(id) {}
    virtual long getCoreLimit(long total_messages) const override {
        return (total_messages / 100000) + 1;
    }
};
