#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <stdint.h>

typedef struct {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} registers_t;

void interrupt_handler(registers_t*);

#endif
