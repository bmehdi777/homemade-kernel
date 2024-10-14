#ifndef __KERNEL_IDT_H
#define __KERNEL_IDT_H

#include <stddef.h>
#include <stdint.h>

// IDT entry
//
// +-----------+-----+-----+-----------+-----------+
// |63                   48|47       40|39       32|
// +-----------+-----+-----+-----------+-----------+
// |Offset                 |Type attr  |Reserved   |
// |                       |           |           |
// |31                   16|           |           |
// +-----------+-----+-----+-----------+-----------+
// |31                   16|15                    0|
// +-----------------------+-----------------------+
// |Segment selector       |Offset                 |
// |                       |                       |
// |15                    0|15                    0|
// +-----------------------+-----------------------+
struct idt_gate_descriptor {
  uint16_t offset_low;
  uint16_t segment_selector;
  uint8_t reserved_zero;   // unused
  uint8_t type_attributes; // gate type, dpl, p fields
  uint16_t offset_high;
} __attribute__((packed));

// whole idt address
struct idt_descriptor {
  uint16_t size;
  uint32_t offset;
} __attribute__((packed));

void initIdt(void);
void setIdtEntry(uint32_t index, uint32_t offset, uint16_t segment_selector,
                 uint8_t type_attributes);

#endif
