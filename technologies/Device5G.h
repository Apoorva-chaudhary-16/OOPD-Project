#pragma once
#include "UserDevice.h"

/**
 * Device5G
 * --------
 * 10 messages per user (packet switching)
 */

class Device5G : public UserDevice {
public:
    Device5G(int id = 0)
        : UserDevice(id, "5G") {}

    virtual int getMessageCount() const override {
        return 10;
    }
};
