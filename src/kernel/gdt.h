#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>
#include <stddef.h>

// gdt entry
struct gdt_segment_descriptor {
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags; // contains limit on bit 48-51 and flags on 52-55
	uint8_t base_high;
}__attribute__((packed)); // ensure the memory layout will be maintained like this

// gdt whole adresse (where it start and where it ends)
struct gdt_descriptor {
	uint16_t size;
	uint32_t offset;
}__attribute__((packed));

void initGdt(void);
void setGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif
