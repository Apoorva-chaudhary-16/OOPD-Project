#pragma once

#include "basicIO.h"
#include "Container.h"
#include "UserDevice.h"

class CellTower {
protected:
    int tower_id;
    long total_spectrum_khz;
    long channel_width_khz;
    int users_per_channel;
    int antennas;

public:
    CellTower(int id = 0)
        : tower_id(id), total_spectrum_khz(0), channel_width_khz(0), users_per_channel(0), antennas(1) {}

    virtual ~CellTower() {}

    virtual long calculateMaxUsers() const = 0;
    virtual int usersInFirstChannel() const = 0;
    virtual void simulate() = 0;
};
