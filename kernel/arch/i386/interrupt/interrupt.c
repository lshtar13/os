#include "interrupt.h"
#include "idt.h"
#include "pic.h"
#include <kernel/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

__attribute__((aligned(0x10))) struct idt_entry idt_entries[IDT_ENTRY_N];
struct idt_ptr idt_ptr;
extern void idt_flush(uint32_t);

void initIdt() {
  printf("initIdt\n");
  idt_ptr.base = (uint32_t)&idt_entries;
  idt_ptr.limit = (sizeof(struct idt_entry) * IDT_ENTRY_N) - 1;
  memset(&idt_entries, 0, sizeof(struct idt_entry) * IDT_ENTRY_N);

  // internal interrupts
  setIdtDescriptor(0, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(1, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(2, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(3, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(4, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(5, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(6, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(7, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(8, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(9, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(10, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(11, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(12, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(13, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(14, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(15, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(16, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(17, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(18, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(19, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(20, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(21, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(22, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(23, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(24, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(25, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(26, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(27, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(28, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(29, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(30, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(31, (uint32_t)isr0, 0x8E);
  setIdtDescriptor(32, (uint32_t)isr0, 0x8E);

  initPic(0x20, 0x28);

  idt_flush((uint32_t)&idt_ptr);
}

void setIdtDescriptor(uint8_t vector, uint32_t isr, uint8_t flags) {
  struct idt_entry *descriptor = &idt_entries[vector];

  descriptor->isr_low = isr & 0xFFFF;
  descriptor->kernel_cs = 0x08;
  descriptor->attributes = flags;
  descriptor->isr_high = isr >> 16;
  descriptor->reserved = 0;
}

void initInterrupt() { initIdt(); }

/* To print the message which defines every exception */
char *exception_messages[] = {"Division By Zero",
                              "Debug",
                              "Non Maskable Interrupt",
                              "Breakpoint",
                              "Into Detected Overflow",
                              "Out of Bounds",
                              "Invalid Opcode",
                              "No Coprocessor",

                              "Double Fault",
                              "Coprocessor Segment Overrun",
                              "Bad TSS",
                              "Segment Not Present",
                              "Stack Fault",
                              "General Protection Fault",
                              "Page Fault",
                              "Unknown Interrupt",

                              "Coprocessor Fault",
                              "Alignment Check",
                              "Machine Check",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",

                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved"};

__attribute__((noreturn)) void isr_handler(struct interrupt_regs reg) {
  char num[INT_STRING_LEN] = {};
  itos(reg.int_no, num);
  printf("%s\n", num);
}
