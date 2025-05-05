#include "timer.h"
#include <kernel/timer.h>

uint32_t tick;

static void timerCallback(struct isr_regs *regs) { ++tick; }

void initTimer(uint32_t freq) {
  cli();

  installIrqHandler(IRQ0, timerCallback);
  tick = 0;

  uint32_t divisor = 119318 / freq;
  outb(0x43, 0x36);
  outb(0x40, (uint8_t)(divisor & 0xFF));
  outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));

  sti();
}
