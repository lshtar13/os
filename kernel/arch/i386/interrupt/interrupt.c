#include "interrupt.h"
#include "pic.h"
#include <kernel/interrupt.h>
#include <stdio.h>

struct idt_entry idt_entries[IDT_ENTRY_N];
struct idt_ptr idt_ptr;
extern void idt_flush(addr_t);
extern void *isr_stub_table[];

void initIdt() {
  idt_ptr.base = (uintptr_t)&idt_entries;
  idt_ptr.limit = (sizeof(struct idt_entry) * IDT_ENTRY_N) - 1;

  for (uint8_t vector = 0; vector < 32; vector++) {
    setIdtDescriptor(vector, isr_stub_table[vector], 0x8E);
  }

  initPic(0x20, 0x28);

  idt_flush(&idt_ptr);
}

void setIdtDescriptor(uint8_t vector, void *isr, uint8_t flags) {
  struct idt_entry *descriptor = &idt_entries[vector];

  descriptor->isr_low = (uint32_t)isr & 0xFFFF;
  descriptor->kernel_cs = 0x08;
  descriptor->attributes = flags;
  descriptor->isr_high = (uint32_t)isr >> 16;
  descriptor->reserved = 0;
}

void exception_handler(struct interrupt_regs *regs) {
  printf("yeah");
  __asm__ volatile("cli; hlt");
}

void initInterrupt() { initIdt(); }