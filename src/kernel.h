#ifndef _KERNEL_H_
#define _KERNEL_H_

// Make sure we are compiling for the correct system.
#if defined(__linux__)
#error "Error: Not using a cross compiler. Fix this immediately."
#endif

// Make sure compiling for the right system.
#if !defined(__i386__)
#error "Error: This is an i386 operating system. You are not using a compiler for that system."
#endif

// Prototype for the kernel_main method. Takes no arguments and returns nothing.
void kernel_main(void);

#endif
