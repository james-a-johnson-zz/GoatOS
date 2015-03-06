#include "idt.h"

#include "string.h"

extern void idt_flush(void);

// The actual interrupt descriptor table.
idt_t idt[256];
// The value representing the idt register.
idtr_t idtr;

// Creates the values put into the idt.
void create_idt_descriptor(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].selector = sel;
    idt[num].zero = 0;

    idt[num].flags = flags;
}

// Creates and loads the idt.
void load_idt() {
    idtr.limit = (sizeof(idtr_t) * 256) - 1;
    idtr.offset = (uint32_t)&idt;

    memset(&idt, 0, sizeof(idt_t)*256);

    create_idt_descriptor(0, (uint32_t)isr0, 0x08, 0x8E);
    create_idt_descriptor(1, (uint32_t)isr1, 0x08, 0x8E);
    create_idt_descriptor(2, (uint32_t)isr2, 0x08, 0x8E);
    create_idt_descriptor(3, (uint32_t)isr3, 0x08, 0x8E);
    create_idt_descriptor(4, (uint32_t)isr4, 0x08, 0x8E);
    create_idt_descriptor(5, (uint32_t)isr5, 0x08, 0x8E);
    create_idt_descriptor(6, (uint32_t)isr6, 0x08, 0x8E);
    create_idt_descriptor(7, (uint32_t)isr7, 0x08, 0x8E);
    create_idt_descriptor(8, (uint32_t)isr8, 0x08, 0x8E);
    create_idt_descriptor(9, (uint32_t)isr9, 0x08, 0x8E);
    create_idt_descriptor(10, (uint32_t)isr10, 0x08, 0x8E);
    create_idt_descriptor(11, (uint32_t)isr11, 0x08, 0x8E);
    create_idt_descriptor(12, (uint32_t)isr12, 0x08, 0x8E);
    create_idt_descriptor(13, (uint32_t)isr13, 0x08, 0x8E);
    create_idt_descriptor(14, (uint32_t)isr14, 0x08, 0x8E);
    create_idt_descriptor(15, (uint32_t)isr15, 0x08, 0x8E);
    create_idt_descriptor(16, (uint32_t)isr16, 0x08, 0x8E);
    create_idt_descriptor(17, (uint32_t)isr17, 0x08, 0x8E);
    create_idt_descriptor(18, (uint32_t)isr18, 0x08, 0x8E);
    create_idt_descriptor(19, (uint32_t)isr19, 0x08, 0x8E);
    create_idt_descriptor(20, (uint32_t)isr20, 0x08, 0x8E);
    create_idt_descriptor(21, (uint32_t)isr21, 0x08, 0x8E);
    create_idt_descriptor(22, (uint32_t)isr22, 0x08, 0x8E);
    create_idt_descriptor(23, (uint32_t)isr23, 0x08, 0x8E);
    create_idt_descriptor(24, (uint32_t)isr24, 0x08, 0x8E);
    create_idt_descriptor(25, (uint32_t)isr25, 0x08, 0x8E);
    create_idt_descriptor(26, (uint32_t)isr26, 0x08, 0x8E);
    create_idt_descriptor(27, (uint32_t)isr27, 0x08, 0x8E);
    create_idt_descriptor(28, (uint32_t)isr28, 0x08, 0x8E);
    create_idt_descriptor(29, (uint32_t)isr29, 0x08, 0x8E);
    create_idt_descriptor(30, (uint32_t)isr30, 0x08, 0x8E);
    create_idt_descriptor(31, (uint32_t)isr31, 0x08, 0x8E);

    idt_flush();
}
