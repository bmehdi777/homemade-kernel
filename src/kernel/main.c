#include "vga.h"
#include "gdt.h"

void kmain(void) {
	initGdt();
	initVga();

	printk("GDT & VGA are init!\n");
}
