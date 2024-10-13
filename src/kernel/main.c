#include "vga.h"

void kmain(void) {
	// init gdt here, before anything else


	init_vga();
	printk("Hello world !\n");
}
