#pragma once
#include "../UserDevice.h"

class Device2G : public UserDevice {
public:
    Device2G(int id = 0) : UserDevice(id, "2G") {}
    virtual int getMessageCount() const override { return 20; } // 5 data + 15 voice
};
