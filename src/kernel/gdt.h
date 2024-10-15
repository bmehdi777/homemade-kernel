#ifndef __KERNEL_GDT_H
#define __KERNEL_GDT_H

#include <stdint.h>
#include <stddef.h>

// GDT entry 
//
// +-----------+-----+-----+-----------+-----------+
// |63       56|55 52|51 48|47       40|39       32|
// +-----------+-----+-----+-----------+-----------+
// |Base       |Flags|Limit|Access byte|Base       |
// |           |     |     |           |           |
// |31       24|3   0|19 16|           |           |
// +-----------+-----+-----+-----------+-----------+
// |31                   16|15                    0|
// +-----------------------+-----------------------+
// |Base                   |Limit                  |
// |                       |                       |
// |15                    0|15                    0|
// +-----------------------+-----------------------+
struct gdt_segment_descriptor {
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags; // contains limit on bit 48-51 and flags on 52-55
	uint8_t base_high;
}__attribute__((packed)); // ensure the memory layout will be maintained like this

// whole gdt address (where it start and where it ends)
struct gdt_descriptor {
	uint16_t size;
	uint32_t offset;
}__attribute__((packed));

struct tss_entry {
	uint32_t link;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldtr;
	uint32_t iopb;
	uint32_t ssp;
}__attribute__((packed));

void initGdt(void);
void setGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void setTSS(uint32_t index, uint32_t ss0, uint32_t esp0);

#endif
