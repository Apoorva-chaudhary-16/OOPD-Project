#pragma once
#include "../UserDevice.h"
class Device5G : public UserDevice {
public:
    Device5G(int id = 0) : UserDevice(id, "5G") {}
    virtual int getMessageCount() const override { return 10; }
};
