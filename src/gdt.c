#include "gdt.h"

// This is the assembly function that will load the gdt register.
extern void flush_gdt(void);

// This is the actual gdt.
uint64_t gdt[5];
// This is what the gdt register will hold.
gdtr_t gdtr;

uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag){
    uint64_t descriptor;

    // create high 32 bit segment
    descriptor  =  limit       & 0x000F0000;    // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;    // set type, p, dpl, s, g, d/b, l, and avl fields 
                                                // If you don't know what these fields are look at 
                                                // the wiki
    descriptor |= (base >> 16) & 0x000000FF;    // set base bits 23:16
    descriptor |=  base        & 0xFF000000;    // set base bits 31:24

    // shift by 32 to allow for the low part of the segment
    descriptor <<= 32;

    // create the low 32 bit segment
    descriptor |= base << 16;                   // set base bits 15:0
    descriptor |= limit & 0x0000FFFF;           // set limit bits 15:0

    return descriptor;
}

void load_gdt(void) {
    gdtr.offset = (uint32_t)&gdt;
    gdtr.limit = (sizeof(uint64_t) * 5) - 1;

    gdt[0] = create_descriptor(0, 0, 0);
    gdt[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    flush_gdt();
}
