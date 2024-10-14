#include "kstdio.h"
#include "lib/str.h"
#include "vga.h"

void printk(char *data) { terminalWrite(data, strlen(data)); }

void errork(char *data) {
  terminalSetColor(vgaEntryColor(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
  terminalWrite("[ERROR] ", 8);
  terminalSetColor(vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminalWrite(data, strlen(data));
	terminalWrite("\n", 1);
}
void infok(char *data) {
  terminalSetColor(vgaEntryColor(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
  terminalWrite("[INFO] ", 7);
  terminalSetColor(vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminalWrite(data, strlen(data));
	terminalWrite("\n", 1);
}
void warningk(char *data) {
  terminalSetColor(vgaEntryColor(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
  terminalWrite("[WARNING] ", 10);
  terminalSetColor(vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminalWrite(data, strlen(data));
	terminalWrite("\n", 1);
}
