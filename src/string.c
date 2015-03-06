#include "string.h"

#include <stdint.h>

// Will return the size of a null terminated string.
// Does this by iterating through the array with an index and
// returns the index of the null in the string.
size_t strlen(const char *c) {
    size_t s = 0;
    while (c[++s]) {}
    return s;
}

// Copies values from one array/pointer to another.
// Will copy values one byte at a time.
void memcpy(const void *s, void *d, size_t n) {
    char *src = (char *)s;
    char *dest = (char *)d;

    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Copies values from one array/pointer to another
// four bytes at a time.
void memcpyw(const void *s, void *d, size_t n) {
    uint32_t *src = (uint32_t *)s;
    uint32_t *dest = (uint32_t *)d;

    size_t i;
    for (i = 0; i < n/4; i++) {
        dest[i] = src[i];
    }

    char *src8 = (char *)s;
    char *dest8 = (char *)d;
    for (i *= 4; i < n; i++) {
        dest8[i] = src8[i];
    }
}

// Will only set one byte per time.
void memset(void *s, const unsigned char v, size_t n) {
    unsigned char *data = (unsigned char *)s;

    for (size_t i = 0; i < n; i++) {
        data[i] = v;
    }
}
