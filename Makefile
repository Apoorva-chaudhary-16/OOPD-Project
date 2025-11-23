# ======================================================
#   Makefile for Cellular Network Simulator (C++11)
# ======================================================

CXX = g++
AS  = nasm
LD  = g++

CXXFLAGS = -c -g -Wall -m64 -O0 -std=c++11 -I.
ASFLAGS  = -f elf64 -g
LDFLAGS  = -g

# ======================================================
#   SOURCE FILES
# ======================================================

SRCS = \
    main.cpp \
    basicIO.cpp \
    Simulator.cpp \
    CellularCore.cpp \
    CellTower.cpp \
    UserDevice.cpp \
    \
    technologies/Tower2G.cpp \
    technologies/Core2G.cpp \
    technologies/Device2G.cpp \
    \
    technologies/Tower3G.cpp \
    technologies/Core3G.cpp \
    technologies/Device3G.cpp \
    \
    technologies/Tower4G.cpp \
    technologies/Core4G.cpp \
    technologies/Device4G.cpp \
    \
    technologies/Tower5G.cpp \
    technologies/Core5G.cpp \
    technologies/Device5G.cpp

OBJS = $(SRCS:.cpp=.o) syscall.o

TARGET = simulator

# ======================================================
#   DEFAULT BUILD TARGET
# ======================================================

all: $(TARGET)

# ======================================================
#   LINKING
# ======================================================

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

# ======================================================
#   COMPILATION RULES
# ======================================================

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

syscall.o: syscall.S
	$(AS) $(ASFLAGS) -o syscall.o syscall.S

# ======================================================
#   CLEAN BUILD FILES
# ======================================================

clean:
	rm -f $(TARGET) $(OBJS)

# ======================================================
#   RUN PROGRAM
# ======================================================

run: all
	./$(TARGET)
