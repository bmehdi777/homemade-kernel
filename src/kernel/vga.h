#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#include <stddef.h>
#include <stdint.h>

enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_YELLOW = 14,
  VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

uint8_t vgaEntryColor(enum vga_color fg, enum vga_color bg);
uint8_t terminalEntryColor(enum vga_color fg, enum vga_color bg);
uint8_t terminalEntry(unsigned char uc, uint8_t color);

void initVga(void);
void terminalClear(void);
void terminalSetColor(uint8_t color);
void terminalScroll(void);
void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y);
void terminalDeleteLastLine(void);
void terminalPutChar(char c);
void terminalWrite(char *data, size_t size);
int handleSpecialCharacter(char character);

void printk(char *data);

#endif
