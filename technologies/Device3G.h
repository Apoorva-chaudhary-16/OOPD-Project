#pragma once
#include "UserDevice.h"

/**
 * Device3G
 * --------
 * 3G device generates:
 *   - 10 messages (both voice + data use packet switching)
 */

class Device3G : public UserDevice {
public:
    Device3G(int id = 0)
        : UserDevice(id, "3G") {}

    virtual int getMessageCount() const override {
        return 10;
    }
};
