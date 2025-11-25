#pragma once
#include "../UserDevice.h"
class Device4G : public UserDevice {
public:
    Device4G(int id = 0) : UserDevice(id, "4G") {}
    virtual int getMessageCount() const override { return 10; }
};
