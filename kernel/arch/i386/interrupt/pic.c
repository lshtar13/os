#include "pic.h"
#include "../io/io.h"

void initPic(int master, int slave) {
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

  outb(PIC1_DATA, master);
  outb(PIC1_DATA, slave);

  outb(PIC1_DATA, 4);
  outb(PIC2_DATA, 2);

  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, 0);
  outb(PIC2_DATA, 0);
}

void picEnd(int irq) {
  if (irq >= 8) {
    outb(PIC2_COMMAND, PIC_EOI);
  }

  outb(PIC1_COMMAND, PIC_EOI);
}