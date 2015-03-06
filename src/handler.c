#include "handler.h"
#include "tty.h"

void interrupt_handler(registers_t* regs) {
    terminal_writestring("Interrupt: ");
    terminal_writehex((uint32_t)regs->int_no);
    terminal_putchar('\n');
}
