#include "gdt.h"
#include "mem.h"

extern void gdt_flush(void*);
extern void tss_flush();

struct gdt_segment_descriptor gdt_entries[6];
struct gdt_descriptor gdt_ptr;
struct tss_entry tss_entry;

void initGdt(void) {
	gdt_ptr.size = (sizeof(struct gdt_segment_descriptor) * 6);
	gdt_ptr.offset = (uint32_t)&gdt_entries;

	setGdtEntry(0,0,0,0,0); // Null descriptor -> required for cpu 
	setGdtEntry(1,0,0xffffffff,0x9a,0xcf); // Kernel mode segment - Code segment
	setGdtEntry(2,0,0xffffffff,0x92,0xcf); // Kernel mode segment - Data segment
	setGdtEntry(3,0,0xffffffff,0xfa,0xcf); // User mode segment - Code segment
	setGdtEntry(4,0,0xffffffff,0xf2,0xcf); // User mode segment - Data segment
	setTSS(5, 0x10, 0x0);
	
	gdt_flush(&gdt_ptr);
	tss_flush();
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

void setTSS(uint32_t index, uint32_t ss0, uint32_t esp0) {
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = base + sizeof(tss_entry);
	setGdtEntry(index, base, limit, 0xe9, 0x0);

	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0 = ss0;
	tss_entry.esp0 = esp0;

	tss_entry.cs = 0x08 | 0x3; // same as in gdt ljmp

	tss_entry.ss = 0x10 | 0x3; // same as segment set in gdt 
	tss_entry.ds = 0x10 | 0x3;
	tss_entry.es = 0x10 | 0x3;
	tss_entry.fs = 0x10 | 0x3;
	tss_entry.ds = 0x10 | 0x3;
}
