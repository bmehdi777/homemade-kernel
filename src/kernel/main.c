#include "vga.h"

void kmain(void) {
	init_vga();
	terminal_write_string("Hello world !\n");
}
