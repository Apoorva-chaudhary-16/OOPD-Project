# Makefile for Cellular Network Simulator (With C++ Threads)

# Compilers
CXX = g++
AS = nasm
LD = g++  # <-- Use g++ as the linker to link libstdc++

# Flags
# -c = Compile, don't link
# -g = Add debug symbols
# -Wall = All warnings
# -m64 = 64-bit
# -O0 = No optimization
# -I. = Look in current directory for includes (basicIO.h)
# We REMOVED: -fno-use-cxa-atexit, -nostdinc++
# We ADDED: -std=c++11 (required for <thread>)
CXXFLAGS = -c -g -Wall -m64 -O0 -std=c++11 -I.

# -f elf64 = 64-bit ELF object file format
ASFLAGS = -f elf64 -g

# -lpthread = Link the POSIX Threads library
# We REMOVED: -nostdlib
LDFLAGS = -g -lpthread

# Object files to build
OBJS = main.o basicIO.o syscall.o

# The final executable name
TARGET = simulator

all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile main.cpp
main.o: main.cpp basicIO.h
	$(CXX) $(CXXFLAGS) -o main.o main.cpp

# Rule to compile basicIO.cpp
# Note: basicIO.cpp now also needs -std=c++11 so it can be linked
basicIO.o: basicIO.cpp basicIO.h
	$(CXX) $(CXXFLAGS) -o basicIO.o basicIO.cpp

# Rule to assemble syscall.S
syscall.o: syscall.S
	$(AS) $(ASFLAGS) -o syscall.o syscall.S

# Rule to clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to build and run
run: all
	./$(TARGET)