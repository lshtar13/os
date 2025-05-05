#include "idt.h"
#include "pic.h"
#include <kernel/interrupt.h>

__attribute__((aligned(0x10))) struct idt_entry idtEntries[IDT_ENTRY_N];
struct idt_ptr idtPtr;
extern void idt_flush(uint32_t);

void initIdt() {
  idtPtr.base = (uint32_t)&idtEntries;
  idtPtr.limit = (sizeof(struct idt_entry) * IDT_ENTRY_N) - 1;
  memset(&idtEntries, 0, sizeof(struct idt_entry) * IDT_ENTRY_N);

  // internal interrupts
  setIdtDescriptor(0, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(1, (uint32_t)isr1, 0x8E);
  setIdtDescriptor(2, (uint32_t)isr2, 0x8E);
  setIdtDescriptor(3, (uint32_t)isr3, 0x8E);
  setIdtDescriptor(4, (uint32_t)isr4, 0x8E);
  setIdtDescriptor(5, (uint32_t)isr5, 0x8E);
  setIdtDescriptor(6, (uint32_t)isr6, 0x8E);
  setIdtDescriptor(7, (uint32_t)isr7, 0x8E);
  setIdtDescriptor(8, (uint32_t)isr8, 0x8E);
  setIdtDescriptor(9, (uint32_t)isr9, 0x8E);
  setIdtDescriptor(10, (uint32_t)isr10, 0x8E);
  setIdtDescriptor(11, (uint32_t)isr11, 0x8E);
  setIdtDescriptor(12, (uint32_t)isr12, 0x8E);
  setIdtDescriptor(13, (uint32_t)isr13, 0x8E);
  setIdtDescriptor(14, (uint32_t)isr14, 0x8E);
  setIdtDescriptor(15, (uint32_t)isr15, 0x8E);
  setIdtDescriptor(16, (uint32_t)isr16, 0x8E);
  setIdtDescriptor(17, (uint32_t)isr17, 0x8E);
  setIdtDescriptor(18, (uint32_t)isr18, 0x8E);
  setIdtDescriptor(19, (uint32_t)isr19, 0x8E);
  setIdtDescriptor(20, (uint32_t)isr20, 0x8E);
  setIdtDescriptor(21, (uint32_t)isr21, 0x8E);
  setIdtDescriptor(22, (uint32_t)isr22, 0x8E);
  setIdtDescriptor(23, (uint32_t)isr23, 0x8E);
  setIdtDescriptor(24, (uint32_t)isr24, 0x8E);
  setIdtDescriptor(25, (uint32_t)isr25, 0x8E);
  setIdtDescriptor(26, (uint32_t)isr26, 0x8E);
  setIdtDescriptor(27, (uint32_t)isr27, 0x8E);
  setIdtDescriptor(28, (uint32_t)isr28, 0x8E);
  setIdtDescriptor(29, (uint32_t)isr29, 0x8E);
  setIdtDescriptor(30, (uint32_t)isr30, 0x8E);
  setIdtDescriptor(31, (uint32_t)isr31, 0x8E);
  setIdtDescriptor(32, (uint32_t)isr32, 0x8E);
  setIdtDescriptor(33, (uint32_t)isr33, 0x8E);

  initPic(0x20, 0x28);

  idt_flush((uint32_t)&idtPtr);
}

void setIdtDescriptor(uint8_t vector, uint32_t isr, uint8_t flags) {
  struct idt_entry *descriptor = &idtEntries[vector];

  descriptor->isr_low = isr & 0xFFFF;
  descriptor->kernel_cs = 0x08;
  descriptor->attributes = flags;
  descriptor->isr_high = isr >> 16;
  descriptor->reserved = 0;
}

void initInterrupt() {
  initIdt();
}
