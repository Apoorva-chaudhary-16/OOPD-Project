#include "basicIO.h"

// Syscall numbers and STD file descriptors
#define SYS_READ  0
#define SYS_WRITE 1
#define STDIN     0
#define STDOUT    1

// External syscall function implemented in syscall.S
extern "C" long syscall3(long number, long arg1, long arg2, long arg3);

// Static buffer for inputstring()
static char inputBuffer[256];

// Global instance
basicIO io;


/* -----------------------------------------------------
 * activateInput()
 * Clears the internal input buffer
 * ---------------------------------------------------*/
void basicIO::activateInput() {
    for (int i = 0; i < 256; ++i)
        inputBuffer[i] = 0;
}


/* -----------------------------------------------------
 * inputint()
 * Reads chars until newline, converts to int
 * ---------------------------------------------------*/
int basicIO::inputint() {
    char buffer[32] = {0};

    long bytes = syscall3(SYS_READ, STDIN, (long)buffer, 31);
    if (bytes <= 0) return 0;

    buffer[bytes] = '\0';

    int result = 0;
    int i = 0;
    bool neg = false;

    if (buffer[0] == '-') {
        neg = true;
        i++;
    }

    while (buffer[i] >= '0' && buffer[i] <= '9') {
        result = result * 10 + (buffer[i] - '0');
        i++;
    }

    return neg ? -result : result;
}


/* -----------------------------------------------------
 * inputstring()
 * Reads up to 255 characters
 * ---------------------------------------------------*/
const char* basicIO::inputstring() {
    syscall3(SYS_READ, STDIN, (long)inputBuffer, 255);
    return inputBuffer;
}


/* -----------------------------------------------------
 * inputstring(buffer, size)
 * Reads into user provided buffer
 * ---------------------------------------------------*/
void basicIO::inputstring(char* buffer, int size) {
    if (!buffer || size <= 0)
        return;

    char ch;
    int i = 0;

    while (i < size - 1) {
        long bytes = syscall3(SYS_READ, STDIN, (long)&ch, 1);
        if (bytes <= 0 || ch == '\n')
            break;
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}


/* -----------------------------------------------------
 * outputint()
 * Writes integer using syscalls only
 * ---------------------------------------------------*/
void basicIO::outputint(int number) {
    char buffer[32];
    int i = 0;
    bool neg = false;

    if (number == 0) {
        buffer[i++] = '0';
    } else {
        if (number < 0) {
            neg = true;
            if (number == -2147483648) {
                outputstring("-2147483648");
                return;
            }
            number = -number;
        }
        while (number > 0) {
            buffer[i++] = '0' + (number % 10);
            number /= 10;
        }
        if (neg) buffer[i++] = '-';
    }

    for (int j = i - 1; j >= 0; --j) {
        syscall3(SYS_WRITE, STDOUT, (long)&buffer[j], 1);
    }
}


/* -----------------------------------------------------
 * outputstring()
 * ---------------------------------------------------*/
void basicIO::outputstring(const char* text) {
    long len = 0;
    while (text[len]) len++;
    syscall3(SYS_WRITE, STDOUT, (long)text, len);
}


/* -----------------------------------------------------
 * terminate() prints newline
 * ---------------------------------------------------*/
void basicIO::terminate() {
    char nl = '\n';
    syscall3(SYS_WRITE, STDOUT, (long)&nl, 1);
}


/* -----------------------------------------------------
 * errorstring()
 * ---------------------------------------------------*/
void basicIO::errorstring(const char* text) {
    long len = 0;
    while (text[len]) len++;
    syscall3(SYS_WRITE, 2, (long)text, len);  // FD=2 = stderr
}


/* -----------------------------------------------------
 * errorint()
 * ---------------------------------------------------*/
void basicIO::errorint(int number) {
    char buffer[32];
    int i = 0;
    bool neg = false;

    if (number == 0) {
        buffer[i++] = '0';
    } else {
        if (number < 0) {
            neg = true;
            if (number == -2147483648) {
                errorstring("-2147483648");
                return;
            }
            number = -number;
        }
        while (number > 0) {
            buffer[i++] = '0' + (number % 10);
            number /= 10;
        }
        if (neg) buffer[i++] = '-';
    }

    for (int j = i - 1; j >= 0; --j) {
        syscall3(SYS_WRITE, 2, (long)&buffer[j], 1);
    }
}
