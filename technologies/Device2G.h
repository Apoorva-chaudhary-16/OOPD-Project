#pragma once
#include "UserDevice.h"

/**
 * Device2G
 * --------
 * Each 2G device generates 20 messages:
 *  - 5 data messages
 *  - 15 voice messages
 */

class Device2G : public UserDevice {
public:
    Device2G(int id = 0)
        : UserDevice(id, "2G") {}

    virtual int getMessageCount() const override {
        return 20;
    }
};
