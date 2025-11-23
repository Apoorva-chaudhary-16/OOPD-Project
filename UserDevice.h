#pragma once

/**
 * Abstract user device class without std::string.
 * Uses char array for technology type.
 */

class UserDevice {
protected:
    int id;
    char techType[16];   // e.g., "2G", "3G", etc.

public:
    UserDevice(int id = 0, const char* type = "") : id(id) {
        int i = 0;
        while (i < 15 && type[i] != '\0') {
            techType[i] = type[i];
            i++;
        }
        techType[i] = '\0';
    }

    virtual ~UserDevice() {}

    int getId() const { return id; }
    const char* getTechType() const { return techType; }

    // Pure virtual
    virtual int getMessageCount() const = 0;
};
