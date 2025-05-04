#include "timer.h"
#include <kernel/timer.h>

#include "../interrupt/isr.h"
#include "../io/io.h"

#include <stdio.h>
#include <string.h>

uint32_t tick, nprint = 0;

#define THRESHOLD 100

static void timerCallback(struct isr_regs *regs) {
  ++tick;
  printf("ticked");
}

void initTimer(uint32_t freq) {
  __asm__ volatile("cli");

  installIrqHandler(IRQ0, timerCallback);

  tick = 0;

  uint32_t divisor = 119318 / freq;

  outb(0x43, 0x36);
  outb(0x40, (uint8_t)(divisor & 0xFF));
  outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
  __asm__ volatile("sti");
}
