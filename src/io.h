#ifndef _IO_H_
#define _IO_H_

#include <stdint.h>

void outb(uint16_t, uint8_t);

uint8_t inb(uint16_t);

uint16_t inw(uint16_t);

#endif
