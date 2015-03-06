#ifndef _STRING_H_
#define _STRING_H_

/*
 * This is the string library. It will define functions that will manipulate
 * and do stuff with memory and char arrays.
 * TODO(jaj): Implement:
 *          Memset, implemented
 *          Memsetw,
 *          Memcpy, implemented
 *          Memcpyw implemented
 * There may be other functions that need to be implemented but for now these
 * are the only ones that are necessary to continue kernel development.
 */

#include <stddef.h>

// A function to return the length of a null terminated char array.
size_t strlen(const char*);

// Copies values from one array/pointer to another.
// Usage is memcpy(src, dest, number of bytes.
void memcpy(const void*, void*, size_t);

// Same as memcpy but it will copy 4 bytes at a time.
void memcpyw(const void*, void*, size_t);

// Sets size_t bytes of what is pointer to by void* to the char value.
void memset(void*, const unsigned char, size_t);

#endif
