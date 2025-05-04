#ifndef __ARCH_I386_ISR_H
#define __ARCH_I386_ISR_H 1

#include <stdint.h>

#define NRESERVED 32
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

struct isr_regs {
  uint32_t cr2;
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, csm, eflags, useresp, ss;
};

typedef void (*isr_t)(struct isr_regs *);

void exception_handler(struct isr_regs *regs);
void isrHandler(uint8_t no, struct isr_regs *regs);
void irqHandler(uint8_t no, struct isr_regs *regs);
uint32_t installIrqHandler(uint8_t isrNo, isr_t handler);

#endif