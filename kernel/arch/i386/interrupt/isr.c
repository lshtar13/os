#include "isr.h"
#include "../io/io.h"
#include <stdint.h>

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

void exception_handler(struct isr_regs *regs) {
  int intNo = regs->int_no;
  if (intNo < NRESERVED) {
    isrHandler(intNo, regs);
  } else {
    irqHandler(intNo, regs);
  }
}

void isrHandler(uint8_t no, struct isr_regs *regs) {
  printf(exception_messages[no]);
  abort();
}

isr_t irqHandlers[16] = {};

uint32_t installIrqHandler(uint8_t isrNo, isr_t handler) {
  int idx = isrNo - NRESERVED;
  irqHandlers[idx] = handler;

  return (uint32_t)irqHandlers[idx];
}

void irqHandler(uint8_t no, struct isr_regs *regs) {
  irqHandlers[no - NRESERVED](regs);
  if (no >= 40) {
    outb(0xA0, 0x20);
  }
  outb(0x20, 0x20);
}
