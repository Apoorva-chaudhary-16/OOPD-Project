#pragma once
#include "NetworkTower.h"
class Tower3G : public NetworkTower {
public:
    Tower3G(basicIO& io) : NetworkTower(io, "3G", 1000, 200, 32, 10, 1) {}
    virtual void simulate() override;
};
