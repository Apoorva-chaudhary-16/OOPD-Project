#include "basicIO.h"

#define SYS_READ  0
#define SYS_WRITE 1
#define STDIN     0
#define STDOUT    1

extern "C" long syscall3(long number, long arg1, long arg2, long arg3);

static char inputBuffer[256];
basicIO io;

void basicIO::activateInput() {
    for (int i = 0; i < 256; ++i) inputBuffer[i] = 0;
}

int basicIO::inputint() {
    char buffer[32] = {0};
    long bytes = syscall3(SYS_READ, STDIN, (long)buffer, 31);
    if (bytes <= 0) return 0;
    if (bytes > 30) bytes = 30;
    buffer[bytes] = '\0';
    int result = 0;
    int i = 0;
    bool neg = false;
    if (buffer[0] == '-') { neg = true; ++i; }
    while (buffer[i] >= '0' && buffer[i] <= '9') {
        result = result * 10 + (buffer[i] - '0');
        ++i;
    }
    return neg ? -result : result;
}

const char* basicIO::inputstring() {
    syscall3(SYS_READ, STDIN, (long)inputBuffer, 255);
    return inputBuffer;
}

void basicIO::inputstring(char* buffer, int size) {
    if (!buffer || size <= 0) return;
    char ch;
    int i = 0;
    while (i < size - 1) {
        long bytes = syscall3(SYS_READ, STDIN, (long)&ch, 1);
        if (bytes <= 0 || ch == '\n') break;
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}

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

void basicIO::outputstring(const char* text) {
    long len = 0;
    while (text[len]) ++len;
    syscall3(SYS_WRITE, STDOUT, (long)text, len);
}

void basicIO::terminate() {
    char nl = '\n';
    syscall3(SYS_WRITE, STDOUT, (long)&nl, 1);
}

void basicIO::errorstring(const char* text) {
    long len = 0;
    while (text[len]) ++len;
    syscall3(SYS_WRITE, 2, (long)text, len);
}

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
