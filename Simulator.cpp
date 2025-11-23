#include "Simulator.h"

// Include all tower classes
#include "technologies/Tower2G.h"
#include "technologies/Tower3G.h"
#include "technologies/Tower4G.h"
#include "technologies/Tower5G.h"

Simulator::Simulator(basicIO& i) : io(i) {}

void Simulator::run() {
    io.outputstring("===== Cellular Network Simulator =====\n");
    io.outputstring("Select Network Technology:\n");
    io.outputstring("1) 2G\n");
    io.outputstring("2) 3G\n");
    io.outputstring("3) 4G\n");
    io.outputstring("4) 5G\n");

    int choice = io.inputint();

    NetworkTower* tower = nullptr;

    switch (choice) {
        case 1:
            tower = new Tower2G(io);
            break;
        case 2:
            tower = new Tower3G(io);
            break;
        case 3:
            tower = new Tower4G(io);
            break;
        case 4:
            tower = new Tower5G(io);
            break;
        default:
            io.errorstring("Invalid choice! Exiting...\n");
            return;
    }

    tower->simulate();   // polymorphism in action

    delete tower;

    io.outputstring("=== Simulation Complete ===\n");
}
