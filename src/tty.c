#include "tty.h"
#include "string.h"

/*
 * This is a library to used for outputting to the terminal screen.
 * The only two functions that should be used for outputting write now are:
 *                  terminal_putchar
 *                  terminal_writestring
 * Functions to output numbers in base ten and base sixteen need to be added.
 * terminal_initialize needs to be called before any of the other functions
 * otherwise you will get undefined behaviour.
 * make_color in combination with terminal_setcolor can be used to change
 * the color of text when outputting to the terminal.
 *
 *
 * TODO(jaj): Implement:
 *              scrolling,         Not currently working
 *              terminal_writehex, Implemented
 *              terminal_writedec,
 *              cursor functions
 */

// Returns a color with the given foreground and background.
// fg will be the color of the text and bg will be the color
// of the screen behind it. Both of these values have to be
// from the vga_color enum defined in tty.h
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
    return (uint8_t)(fg | bg << 4);
}

// Creates the actually bits stored in memory for a given character and color.
uint16_t make_vgaentry(char c, uint8_t color) {
    uint16_t c16 = (uint16_t)c;
    uint16_t color16 = (uint16_t)color;
    return (uint16_t)(c16 | color16 << 8);
}

// Initializes all of the values needed to get the terminal functions to work.
// This will also clear the screen.
// Right now the default color is white on black. Changed from cyan on light grey.
// Cyan on light grey was cool but hard to read.
void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_WHITE, COLOR_BLACK);
    terminal_buffer = (uint16_t*)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = make_vgaentry(' ', terminal_color);
        }
    }
}

// This will change the color used when using the function putchar and writestring.
// It will change default color to the one passed to it.
// This color should be created with the make_color function.
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

// This puts a character with given color at the specified point.
// This should not be used outside of this library.
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

// Will put a character at the next point.
void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            scroll();
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            if (++terminal_row == VGA_HEIGHT) {
                scroll();
            }
        }
    }
}

// Writes a string to the terminal screen.
void terminal_writestring(const char *data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) {
        terminal_putchar(data[i]);
    }
}

// This will scroll the screen up one. Specifically moves each row of the screen up one row
// and leaves the bottom row blank.
void scroll() {
    for (size_t i = 0; i < VGA_WIDTH*(VGA_HEIGHT-1); i++) {
        terminal_buffer[i] = terminal_buffer[i+80];
    }

    uint16_t empty = make_vgaentry(' ', terminal_color);
    for (size_t i = VGA_WIDTH * (VGA_HEIGHT-1); i < VGA_HEIGHT * VGA_WIDTH; i++) {
        terminal_buffer[i] = empty;
    }

    terminal_column = 0;
    terminal_row = VGA_HEIGHT-1;
}

// Will write the given uint32_t number to the screen in base 16.
void terminal_writehex(uint32_t n) {
    char string[] = {'0', 'x', '0', '0', '0', '0', '0', '0', '0', '0', 0};

    size_t i = 9;
    while (n) {
        string[i] = (char)(n % 16 > 9)? '7' + n%16 : '0' + n%16;
        i--;
        n /= 16;
    }

    terminal_writestring(string);
}

// Write a uint32_t to terminal screen in base 10.
void terminal_writedec(uint32_t n) {
    char string[] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 0};

    size_t i = 9;
    while (n) {
        string[i] = (char)'0' + n%10;
        i--;
        n /= 10;
    }

    terminal_writestring(string);
}
