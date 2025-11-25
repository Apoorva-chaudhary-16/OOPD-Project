#pragma once
#include "basicIO.h"

class Simulator {
private:
    basicIO& io;
public:
    Simulator(basicIO& i);
    void run();
};
