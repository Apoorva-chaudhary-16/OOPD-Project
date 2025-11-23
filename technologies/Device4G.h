#pragma once
#include "UserDevice.h"

/**
 * Device4G
 * --------
 * 4G user device = 10 messages per connection
 */

class Device4G : public UserDevice {
public:
    Device4G(int id = 0)
        : UserDevice(id, "4G") {}

    virtual int getMessageCount() const override {
        return 10;
    }
};
