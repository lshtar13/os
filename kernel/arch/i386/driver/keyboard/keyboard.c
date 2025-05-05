#include "keyboard.h"
#include <stdio.h>

static void keyboardCallback(struct isr_regs *regs) {
  char scanCode = inb(0x60) & 0x7F; // What key is pressed
  char press = inb(0x60) & 0x80;    // Press down, or released
  printf("pressed");
}

void initKeyboard() {
  cli();

  installIrqHandler(IRQ1, keyboardCallback);

  sti();
}