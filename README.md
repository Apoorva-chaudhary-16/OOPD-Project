========================================
      CELLULAR NETWORK SIMULATOR
========================================

Course: Object Oriented Programming & Design  
Language Used: C++ (NO STL, NO STANDARD I/O)  
All Input/Output is performed ONLY using provided:
➤ basicIO.h  
➤ basicIO.cpp  
➤ syscall.S  

========================================
Project Description
========================================

This project simulates the working of different cellular network
technologies: 2G, 3G, 4G and 5G. It uses Object Oriented Principles:
✔ Inheritance
✔ Data Hiding
✔ Data Abstraction
✔ Polymorphism
✔ Exception Handling (Custom)

Three main components are modeled:
1) Cellular Core  
2) User Device  
3) Cell Tower

Each network (2G/3G/4G/5G) has separate:
➤ Tower class  
➤ Core class  
➤ Device class  

Simulation calculates:
✔ Total supported users
✔ Capacity based on file input
✔ Overflow users (if any)
✔ Assignment of users to frequency channels
✔ Message overhead & total messages
✔ Number of cores required

========================================
Input Format
========================================

The simulator takes input from the user as a filename (example: input.txt).
This file MUST be present in the same folder as the compiled binary.

FILE FORMAT:
Line 1 → TOTAL USERS REQUESTED
Next lines → Users expected in each channel (space OR newline separated)

Example (input.txt):
----------------------------------------
40
5 10 8 6 4 7 0 0 0 0 0
----------------------------------------

NOTES:
✔ File may request MORE users than supported → Simulator reports overflow.
✔ For 4G and 5G, extra channels exist (file can give fewer/more values).

========================================
How to Build (Compilation Instructions)
========================================

Run the following command in terminal inside the project folder:

    make

This will generate the executable:

    cellsim

========================================
How to Run
========================================

Execute:

    ./cellsim

Then:
1) Select Technology (1 to 5)
2) Enter the input filename (Ex: input.txt)
3) Enter core overhead percentage (0 - 100)
4) Enter core capacity (# maximum messages one core can handle)

========================================
Files in Project
========================================

basicIO.h  
basicIO.cpp  
syscall.S  
main.cpp  
Simulator.h  
Simulator.cpp  

=== Network Base Classes ===
CellularCore.h / CellularCore.cpp  
UserDevice.h  / UserDevice.cpp  
NetworkTower.h / NetworkTower.cpp (if applicable)

=== Technology Implementations ===
technologies/
    Tower2G.h / Tower2G.cpp
    Core2G.h  / Core2G.cpp
    Device2G.h / Device2G.cpp

    Tower3G.h / Tower3G.cpp
    Core3G.h  / Core3G.cpp
    Device3G.h / Device3G.cpp

    Tower4G.h / Tower4G.cpp
    Core4G.h  / Core4G.cpp
    Device4G.h / Device4G.cpp

    Tower5G.h / Tower5G.cpp
    Core5G.h  / Core5G.cpp
    Device5G.h / Device5G.cpp

========================================
End of README
========================================
