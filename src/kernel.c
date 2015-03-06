#include "kernel.h"
#include "tty.h"
#include "gdt.h"

#include <stdint.h>

// A simple kernel main function that will be used to test
// anything that is implemented.
void kernel_main() {
    asm volatile ("int $0x00");
    asm volatile ("int $0x01");

    terminal_writehex(0x000AE112);
}
