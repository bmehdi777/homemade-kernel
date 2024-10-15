#include "idt.h"
#include "mem.h"

extern void idt_flush(void*);

struct idt_gate_descriptor idt_entries[256];
struct idt_descriptor idt_ptr;


void initIdt(void) {
	idt_ptr.size = (sizeof(struct idt_gate_descriptor)*256);
	idt_ptr.offset = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(struct idt_gate_descriptor)*256);

}

void setIdtEntry(uint32_t index, uint32_t offset, uint16_t segment_selector,
                 uint8_t type_attributes) {
	idt_entries[index].offset_low = (offset & 0xFFFF);
	idt_entries[index].offset_high = (offset >> 16) & 0xFFFF;
}
