#pragma once

class UserDevice {
protected:
    int id;
    char techType[12];
public:
    UserDevice(int id = 0, const char* type = "") : id(id) {
        int i = 0;
        while (i < 11 && type[i]) { techType[i] = type[i]; ++i; }
        techType[i] = '\0';
    }
    virtual ~UserDevice() {}
    int getId() const { return id; }
    const char* getTechType() const { return techType; }
    virtual int getMessageCount() const = 0;
};
