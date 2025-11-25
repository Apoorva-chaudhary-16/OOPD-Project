#pragma once
#include "NetworkTower.h"

class Tower2G : public NetworkTower {
public:
    Tower2G(basicIO& io) : NetworkTower(io, "2G", 1000, 200, 16, 20, 1) {}
    virtual void simulate() override;
};
