#include "vga.h"
#include "gdt.h"

void kmain(void) {
	initGdt();
	//initVga();
	//printk("GDT is init !\r\n");
}
