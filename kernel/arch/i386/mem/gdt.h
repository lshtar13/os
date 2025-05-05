#ifndef _ARCH_I386_GDT_H
#define _ARCH_I386_GDT_H

#include <stdint.h>

#define GDT_ENTRY_N 5

struct gdt_entry {
  uint16_t limit;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t flags;
  uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
  uint16_t limit;
  unsigned int base;
} __attribute__((packed));

void initGdt();
void setGdtEntry(uint32_t idx, uint32_t base, uint32_t limit, uint8_t access,
                 uint8_t flags);

#endif