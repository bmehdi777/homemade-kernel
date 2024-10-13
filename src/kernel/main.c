#include "vga.h"

void kmain(void) {
	init_vga();
	printk("Hello world !\n");
}
