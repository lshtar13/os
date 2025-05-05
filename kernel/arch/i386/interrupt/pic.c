#include "pic.h"

void initPic(int masterOffset, int slaveOffset) {

  // start initialization
  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

  // set interrupt offset
  outb(PIC1_DATA, masterOffset);
  outb(PIC1_DATA, slaveOffset);

  // tell about cascade
  outb(PIC1_DATA, 4);
  outb(PIC2_DATA, 2);

  // tell which mode is used
  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  // unmask
  outb(PIC1_DATA, 0);
  outb(PIC2_DATA, 0);
}

void picEnd(int irq) {
  if (irq >= 8) {
    outb(PIC2_COMMAND, PIC_EOI);
  }

  outb(PIC1_COMMAND, PIC_EOI);
}