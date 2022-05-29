#include "text.h"

uint16_t* video_mem = (uint16_t*)(0xB8000);
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t to_hex(uint8_t color, char c) {
    return (color << 8) | c;
}

size_t strlen(const char* s) {
    int i = 0;
    while(s[i++]);
    return i;
}

void terminal_writechar(char c, uint8_t color) {
    if(c == '\n') {
        terminal_row++;
        terminal_col = 0;
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, color);
    terminal_col++;
    if(terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row++;
    }
}

void terminal_putchar(int x, int y, char c, uint8_t color) {
    video_mem[(y * VGA_WIDTH) + x] = to_hex(color, c);
}

void print(const char* s) {
    for(int i = 0; i < strlen(s); i++) {
        terminal_writechar(s[i], 15);
    }
}
