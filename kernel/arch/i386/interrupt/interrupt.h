#ifndef __ARCH_I386_IDT_H
#define __ARCH_I386_IDT_H

#include <stdint.h>

#define IDT_ENTRY_N 256

struct idt_entry {
  uint16_t isr_low;
  uint16_t kernel_cs;
  uint8_t reserved;
  uint8_t attributes;
  uint16_t isr_high;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct interrupt_regs {
  uint32_t cr2;
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, csm, eflags, useresp, ss;
};

void initIdt();
void setIdtDescriptor(uint8_t vector, void *isr, uint8_t flags);
__attribute__((noreturn)) void exception_handler(struct interrupt_regs *regs);

#endif