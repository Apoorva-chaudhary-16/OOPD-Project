#pragma once

#ifndef BASIC_IO_H
#define BASIC_IO_H

class basicIO {
public:
    void activateInput();
    int inputint();
    const char* inputstring();
    void inputstring(char* buffer, int size);
    void outputint(int value);
    void outputstring(const char* text);
    void terminate();
    void errorstring(const char* text);
    void errorint(int number);
};

extern basicIO io;

#endif
