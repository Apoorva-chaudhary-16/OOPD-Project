#pragma once

#ifndef BASIC_IO_H
#define BASIC_IO_H

/**
 * basicIO
 * -------
 * Custom low-level IO class required by the OOPD project.
 * Uses syscall3() defined in syscall.S.
 *
 * Allowed operations:
 *   - activateInput()
 *   - inputint()
 *   - inputstring()
 *   - outputint()
 *   - outputstring()
 *   - errorstring()
 *   - errorint()
 */

class basicIO {
public:
    void activateInput();

    // Read integer
    int inputint();

    // Read full string into internal buffer
    const char* inputstring();

    // Read into user-provided buffer
    void inputstring(char* buffer, int size);

    // Output integer
    void outputint(int value);

    // Output string
    void outputstring(const char* text);

    // Print newline
    void terminate();

    // Error output
    void errorstring(const char* text);
    void errorint(int number);
};

// Global object required by the specification
extern basicIO io;

#endif
