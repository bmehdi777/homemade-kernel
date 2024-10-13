#include "gdt.h"

extern void gdt_flush(void*);

struct gdt_segment_descriptor gdt_entries[5];
struct gdt_descriptor gdt_ptr;

void initGdt(void) {
	gdt_ptr.size = (sizeof(struct gdt_segment_descriptor) * 5);
	gdt_ptr.offset = (uint32_t)&gdt_entries;

	setGdtEntry(0,0,0,0,0); // Null descriptor -> required for cpu 
	setGdtEntry(1,0,0xffffffff,0x9a,0xcf); // Kernel mode segment - Code segment
	setGdtEntry(2,0,0xffffffff,0x92,0xcf); // Kernel mode segment - Data segment
	setGdtEntry(3,0,0xffffffff,0xfa,0xcf); // User mode segment - Code segment
	setGdtEntry(4,0,0xffffffff,0xf2,0xcf); // User mode segment - Data segment
	
	gdt_flush(&gdt_ptr);
}

void setGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	gdt_entries[index].base_low = (base & 0xFFFF);
	gdt_entries[index].base_middle = (base >> 16) & 0xFF;
	gdt_entries[index].base_high = (base >> 24) & 0xFF;

	gdt_entries[index].limit = (limit & 0xFFFF);
	gdt_entries[index].flags = (limit >> 16) & 0x0F;
	gdt_entries[index].flags |= (flags & 0xF0);
	gdt_entries[index].access = access;
}
