#ifndef TEXT_HEADER
#define TEXT_HEADER

#include <stddef.h>
#include <stdint.h>

#define VGA_HEIGHT 20
#define VGA_WIDTH 80

size_t strlen(const char*);

uint16_t to_hex(uint8_t, char);

void terminal_putchar(int x, int y, char c, uint8_t color);

void print(const char*);

#endif
