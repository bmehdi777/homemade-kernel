#include "vga.h"
#include <stdint.h>

void kmain(void) {
	uint16_t* buffer = (uint16_t*) 0xB8000; 
	*buffer = (uint16_t) 0x2f4b2f4f;

	init_vga();
	terminal_clear();

	
	terminal_write_string("Hello world !\n");
}
