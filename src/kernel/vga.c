#include "vga.h"
#include "lib/str.h"

uint8_t vgaEntryColor(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}
uint16_t vgaEntry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer = (uint16_t *)0xB8000;

void initVga(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminalClear();
}
void terminalClear(void) {
  for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
    for (uint16_t x = 0; x < VGA_WIDTH; x++) {
      uint16_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vgaEntry(' ', terminal_color);
    }
  }
}
void terminalSetColor(uint8_t color) { terminal_color = color; }

void terminalScroll(void) {
  for (uint16_t y = 1; y <= VGA_HEIGHT - 1; y++) {
    for (uint16_t x = 0; x < VGA_WIDTH; x++) {
      uint16_t old_index = (y-1) * VGA_WIDTH  + x;
			uint16_t cur_index = y * VGA_WIDTH + x;
			terminal_buffer[old_index] = terminal_buffer[cur_index];
		}
	}
}
void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
	size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vgaEntry(c, color);
}

void terminalDeleteLastLine(void) {
	for (uint16_t x = 0; x < VGA_WIDTH; x++) {
		uint16_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		terminal_buffer[index] = vgaEntry(' ', terminal_color);
	}
}

void terminalPutChar(char c) {
  if (terminal_column+1 == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
      terminalScroll();
      terminalDeleteLastLine();
      terminal_row = VGA_HEIGHT - 1;
    }
  }

  if (terminal_row == VGA_HEIGHT) {
    terminal_row++;
    terminalScroll();
    terminalDeleteLastLine();
    terminal_row = VGA_HEIGHT - 1;
  }
	terminalPutEntryAt(c, terminal_color, terminal_column, terminal_row);
	terminal_column++;
}
void terminalWrite(char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (!handleSpecialCharacter(data[i])) {
      terminalPutChar(data[i]);
    }
  }
}

int handleSpecialCharacter(char character) {
  switch (character) {
  case '\n':
    terminal_row += 1;
    terminal_column = 0;
    break;
  case '\t':
    terminal_column += 4;
    break;
  default:
    return 0;
  }

  return 1;
}
