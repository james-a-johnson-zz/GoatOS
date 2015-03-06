#ifndef _TTY_H_
#define _TTY_H_

// These defines define the height and width of the terminal screen.
// These are used to see if when need to move to the next line and
// eventually to see if scrolling is needed.
// 80 * 25 is the default terminal screen size when control is passed
// to the kernel after the bootloader has run.
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include <stdint.h>
#include <stddef.h>

// These are the colors that can be used in VGA mode.
enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15
};

// These are globals used for when writing to the video memory.
// terminal_row and terminal_column with also represent the position of cursor when that is finally implemented.
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

// What these functions do and how to use them can be found in the comments of tty.c
// Please look there if you have any questions.
uint8_t make_color(enum vga_color, enum vga_color);
uint16_t make_vgaentry(char, uint8_t);
void terminal_initialize(void);
void terminal_setcolor(uint8_t);
void terminal_putentryat(char, uint8_t, size_t, size_t);
void terminal_putchar(char);
void terminal_writestring(const char*);
void scroll(void);
void terminal_writehex(uint32_t);
void terminal_writedec(uint32_t);

#endif
