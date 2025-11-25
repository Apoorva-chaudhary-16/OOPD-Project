#pragma once
#include "NetworkTower.h"
class Tower4G : public NetworkTower {
public:
    Tower4G(basicIO& io) : NetworkTower(io, "4G", 1000, 10, 30, 10, 4) {}
    virtual void simulate() override;
};
