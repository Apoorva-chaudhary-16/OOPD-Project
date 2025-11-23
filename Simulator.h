#pragma once

#include "basicIO.h"

/**
 * Simulator orchestrates the entire program:
 *  - Displays menu
 *  - Takes input using BasicIO
 *  - Creates the correct Tower object (2G/3G/4G/5G)
 *  - Runs polymorphic simulation
 */
class Simulator {
private:
    basicIO& io;   // reference to global I/O object

public:
    Simulator(basicIO& i);
    void run();
};
