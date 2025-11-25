#pragma once
#include "NetworkTower.h"
class Tower5G : public NetworkTower {
public:
    Tower5G(basicIO& io) : NetworkTower(io, "5G (1800 MHz)", 10000, 1000, 30, 10, 16) {}
    virtual void simulate() override;
};
