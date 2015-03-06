#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>

// This represents the interrupt descriptor table. The actual structure is pulled
// from James Molloy's kernel development tutorial. You can learn more about what
// the specific parts of the struct does at his website www.jamesmolloy.co.uk/tutorial_html/
typedef struct {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_t;

// This is the structure that represents the idt register. It is the same exact structure
// as the gdt register structure.
typedef struct {
    uint16_t limit;
    uint32_t offset;
} __attribute__((packed)) idtr_t;

// Create the idt and load it into the idt register.
void load_idt(void);

// This will load a value of the idt at the specified location.
void create_idt_descriptor(uint8_t, uint32_t, uint16_t, uint8_t);

// These are externs for all of the interrupt handlers that will be defined in an
// assembly file so that they can be used in C.
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

#endif
