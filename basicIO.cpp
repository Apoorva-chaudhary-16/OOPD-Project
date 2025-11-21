#include "basicIO.h" // Changed from ../include/basicIO.h for simplicity
//#include "BlockStandardIO.h" // This file was not provided, but code works without it

#define SYS_READ 0
#define SYS_WRITE 1
#define STDIN 0
#define STDOUT 1


basicIO io; // Definition of the global 'io' object

extern "C" long syscall3(long number, long arg1, long arg2, long arg3);

static char inputBuffer[256];

void basicIO::activateInput() {
    for (int i = 0; i < 256; ++i) inputBuffer[i] = 0;
}

int basicIO::inputint() {
    char buffer[32] = {0};
    long bytes = syscall3(0, 0, (long)buffer, 31);
    if (bytes <= 0) return 0;
    buffer[bytes] = '\0';
    int result = 0;
    int i = 0;
    bool neg = false;
    if (buffer[0] == '-') {
        neg = true;
        i++;
    }
    for (; buffer[i] >= '0' && buffer[i] <= '9'; ++i) {
        result = result * 10 + (buffer[i] - '0');
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
    bool isNegative = false;
    if (number == 0) {
        buffer[i++] = '0';
    } else {
        if (number < 0) {
            isNegative = true;
            if (number == -2147483648) { // Handle INT_MIN
                outputstring("-2147483648");
                return;
            }
            number = -number;
        }
        while (number > 0) {
            buffer[i++] = '0' + (number % 10);
            number /= 10;
        }
        if (isNegative) {
            buffer[i++] = '-';
        }
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
    char newline = '\n';
    syscall3(SYS_WRITE, STDOUT, (long)&newline, 1);
}

void basicIO::errorstring(const char* text) {
    long len = 0;
    while (text[len]) ++len;
    syscall3(SYS_WRITE, 2, (long)text, len); // 2 is stderr
}

void basicIO::errorint(int number) {
    char buffer[32];
    int i = 0;
    bool isNegative = false;
    if (number == 0) {
        buffer[i++] = '0';
    } else {
        if (number < 0) {
            isNegative = true;
            if (number == -2147483648) { // Handle INT_MIN
                errorstring("-2147483648");
                return;
            }
            number = -number;
        }
        while (number > 0) {
            buffer[i++] = '0' + (number % 10);
            number /= 10;
        }
        if (isNegative) {
            buffer[i++] = '-';
        }
    }
    for (int j = i - 1; j >= 0; --j) {
        syscall3(SYS_WRITE, 2, (long)&buffer[j], 1); // 2 is stderr
    }
}

// REMOVED EXTRA '}' that was here in your original file