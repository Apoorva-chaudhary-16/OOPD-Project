#include "basicIO.h"
#include "Simulator.h"

/**
 * MAIN ENTRY POINT
 * ----------------
 * Uses the global BasicIO object (io)
 * and runs the Simulator interface.
 */

int main() {
    Simulator sim(io);
    sim.run();
    return 0;
}
