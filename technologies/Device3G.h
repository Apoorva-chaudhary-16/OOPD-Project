#pragma once
#include "../UserDevice.h"

class Device3G : public UserDevice {
public:
    Device3G(int id = 0) : UserDevice(id, "3G") {}
    virtual int getMessageCount() const override { return 10; }
};
