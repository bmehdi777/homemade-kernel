#include "vga.h"
#include "kstdio.h"
#include "gdt.h"

void kmain(void) {
	initGdt();
	initVga();

	infok("GDT & VGA are init!");
	errork("Test error");
	warningk("Test warning");
}
