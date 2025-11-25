# Cellular Network Simulator

**Object-Oriented Programming & Design Project**

---

## 📋 Overview

This project simulates cellular network technologies (2G, 3G, 4G, and 5G) using core Object-Oriented Programming principles. The simulator models real-world cellular infrastructure components and calculates network capacity, user allocation, and system overhead.

### Key Features

- **Multi-technology support**: 2G, 3G, 4G, and 5G network simulation
- **Realistic modeling**: Cellular Core, User Devices, and Cell Towers
- **Capacity analysis**: Calculates supported users, overflow, and resource allocation
- **Custom I/O system**: Implements low-level I/O without standard library dependencies

---

## 🎯 Technical Implementation

### Language & Constraints

- **Language**: C++
- **No STL**: Standard Template Library not used
- **No Standard I/O**: Custom I/O implementation via provided files:
  - `basicIO.h`
  - `basicIO.cpp`
  - `syscall.S`

### Object-Oriented Principles Applied

- **Inheritance**: Technology-specific classes inherit from base network components
- **Data Hiding**: Private member variables with controlled access
- **Data Abstraction**: Abstract interfaces for network components
- **Polymorphism**: Runtime behavior variation across network technologies
- **Exception Handling**: Custom exception classes for error management

### Architecture

The simulator uses a three-tier architecture:

```
┌─────────────────┐
│ Cellular Core   │ ← Handles message routing and user management
├─────────────────┤
│ Cell Tower      │ ← Manages frequency channels and user connections
├─────────────────┤
│ User Device     │ ← Represents individual network subscribers
└─────────────────┘
```

Each network generation (2G/3G/4G/5G) implements its own specialized classes for all three components.

---

## 📊 Simulation Metrics

The simulator calculates and reports:

- **Total supported users**: Maximum capacity for selected technology
- **Channel allocation**: Distribution of users across frequency channels
- **Overflow analysis**: Users exceeding network capacity
- **Message overhead**: Communication efficiency metrics
- **Total messages**: Aggregate message count across the network
- **Core requirements**: Number of cellular cores needed for the load

---

## 🔧 Build Instructions

### Prerequisites

- C++ compiler (g++ recommended)
- Make utility
- Unix-like environment (Linux/macOS) or WSL on Windows

### Compilation

Navigate to the project directory and run:

```bash
make
```

This generates the executable: **`cellsim`**

### Clean Build

To remove compiled objects and rebuild:

```bash
make clean
make
```

---

## 🚀 Usage

### Running the Simulator

```bash
./cellsim
```

### Interactive Prompts

1. **Select Network Technology**
   - Enter `1` for 2G
   - Enter `2` for 3G
   - Enter `3` for 4G
   - Enter `4` for 5G
   - Enter `5` to exit

2. **Input Filename**
   - Provide the name of your input file (e.g., `input.txt`)
   - File must be in the same directory as the executable

3. **Core Overhead Percentage**
   - Enter a value between 0-100
   - Represents processing overhead for message handling

4. **Core Capacity**
   - Enter maximum messages a single core can process
   - Determines how many cores are needed

---

## 📄 Input File Format

### Structure

```
<TOTAL_USERS>
<CHANNEL_1> <CHANNEL_2> <CHANNEL_3> ... <CHANNEL_N>
```

### Example: `input.txt`

```
40
5 10 8 6 4 7 0 0 0 0 0
```

**Interpretation:**
- Total users requested: 40
- Channel 1: 5 users
- Channel 2: 10 users
- Channel 3: 8 users
- Channels 4-7: (4, 7, 0, 0 users respectively)
- Channels 8-11: 0 users (unused)

### Important Notes

- **Flexible spacing**: Channel values can be space or newline separated
- **Overflow handling**: If total users exceed network capacity, overflow is reported
- **Variable channels**: 4G and 5G support additional channels; fewer or more values can be provided
- **Zero channels**: Unused channels can be marked with 0

---

## 📁 Project Structure

```
cellular-network-simulator/
├── basicIO.h                    # Custom I/O header
├── basicIO.cpp                  # Custom I/O implementation
├── syscall.S                    # System call assembly
├── main.cpp                     # Entry point
├── Simulator.h                  # Main simulator header
├── Simulator.cpp                # Main simulator implementation
│
├── CellularCore.h               # Base core class
├── CellularCore.cpp
├── UserDevice.h                 # Base device class
├── UserDevice.cpp
├── NetworkTower.h               # Base tower class
├── NetworkTower.cpp
│
└── technologies/                # Technology-specific implementations
    ├── Tower2G.h
    ├── Tower2G.cpp
    ├── Core2G.h
    ├── Core2G.cpp
    ├── Device2G.h
    ├── Device2G.cpp
    │
    ├── Tower3G.h
    ├── Tower3G.cpp
    ├── Core3G.h
    ├── Core3G.cpp
    ├── Device3G.h
    ├── Device3G.cpp
    │
    ├── Tower4G.h
    ├── Tower4G.cpp
    ├── Core4G.h
    ├── Core4G.cpp
    ├── Device4G.h
    ├── Device4G.cpp
    │
    ├── Tower5G.h
    ├── Tower5G.cpp
    ├── Core5G.h
    ├── Core5G.cpp
    ├── Device5G.h
    └── Device5G.cpp
```

---

## 🔍 Example Workflow

### Step-by-step Execution

1. **Prepare Input File**
   ```
   echo "40" > input.txt
   echo "5 10 8 6 4 7 0 0 0 0 0" >> input.txt
   ```

2. **Compile the Project**
   ```bash
   make
   ```

3. **Run the Simulator**
   ```bash
   ./cellsim
   ```

4. **Provide Inputs**
   ```
   Select Technology: 4
   Enter filename: input.txt
   Enter core overhead (0-100): 15
   Enter core capacity: 1000
   ```

5. **View Results**
   - Total supported users
   - Users per channel
   - Overflow count (if any)
   - Number of cores required
   - Message overhead and total messages

---

## ⚠️ Constraints & Limitations

- **No STL containers**: Arrays and manual memory management only
- **No iostream**: All I/O through custom `basicIO` functions
- **File location**: Input files must be in the same directory as the executable
- **Single tower simulation**: Each run simulates one tower of the selected technology

---

## 🛠️ Troubleshooting

### Common Issues

**Problem**: `make: command not found`
- **Solution**: Install build-essential (Linux) or Xcode Command Line Tools (macOS)

**Problem**: Input file not found
- **Solution**: Ensure the input file is in the same directory as `./cellsim`

**Problem**: Compilation errors
- **Solution**: Verify all source files are present and check compiler compatibility

**Problem**: Segmentation fault
- **Solution**: Check input file format and ensure values are valid integers

---
