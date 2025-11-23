#pragma once

/**
 * Custom error codes (since we cannot use <exception> or C++ exception classes)
 *
 * Use them like:
 *      return ERROR_OVER_CAPACITY;
 * or
 *      io.errorstring("Over capacity!\n");
 */

#define ERROR_INVALID_INPUT    1
#define ERROR_OVER_CAPACITY    2
#define ERROR_CORE_LIMIT       3

