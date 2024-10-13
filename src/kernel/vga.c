#include "vga.h"
#include "lib/str.h"


uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}
uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer = (uint16_t*) 0xB8000;

void init_vga(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_clear();
}
void terminal_clear(void) {
  for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
    for (uint16_t x = 0; x < VGA_WIDTH; x++) {
      uint16_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}
void terminal_set_color(uint8_t color) { terminal_color = color; }
void terminal_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
  size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}
void terminal_put_char(char c) {
  terminal_put_entry_at(c, terminal_color, terminal_column, terminal_row);
  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
      terminal_row = 0;
    }
  }
}
void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_put_char(data[i]);
  }
}
void terminal_write_string(const char *data) {
  terminal_write(data, strlen(data));
}
