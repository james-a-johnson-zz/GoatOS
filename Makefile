CC = /home/jaj/Documents/cross/bin/i686-elf-gcc

WARNINGS = -W -Wall -Wextra -Werror -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	-Wuninitialized -Wstrict-prototypes

CFLAGS = $(WARNINGS) -std=gnu11 -ffreestanding -O2

COBJECTS = $(subst src,build,$(patsubst %.c,%.o,$(wildcard src/*.c)))
ASMOBJECTS = $(subst src,build,$(patsubst %.asm,%.o,$(wildcard src/*.asm)))

.PHONY: all run clean

all: $(COBJECTS) $(ASMOBJECTS)
	$(CC) -T linker.ld -o bin/myos.bin -nostdlib $(CFLAGS) build/*.o -lgcc

build/boot.o: src/boot.asm
	nasm -f elf32 -o build/boot.o src/boot.asm

build/interrupt.o: src/interrupt.asm
	nasm -f elf32 -o build/interrupt.o src/interrupt.asm

build/kernel.o: src/kernel.h src/kernel.c
	$(CC) $(CFLAGS) -c -o build/kernel.o src/kernel.c

build/string.o: src/string.h src/string.c
	$(CC) $(CFLAGS) -c -o build/string.o src/string.c

build/tty.o: src/tty.h src/tty.c
	$(CC) $(CFLAGS) -c -o build/tty.o src/tty.c

build/gdt.o: src/gdt.h src/gdt.c
	$(CC) $(CFLAGS) -c -o build/gdt.o src/gdt.c

build/idt.o: src/idt.h src/idt.c
	$(CC) $(CFLAGS) -c -o build/idt.o src/idt.c

build/handler.o: src/handler.h src/handler.c
	$(CC) $(CFLAGS) -c -o build/handler.o src/handler.c

run:
	qemu-system-i386 -kernel bin/myos.bin

clean:
	rm -rf build/*
	rm -rf bin/*
