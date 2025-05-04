#include "util.h"

void outb(uint16_t Port, uint8_t Value) {
  asm volatile("outb %1, %0" : : "dN"(Port), "a"(Value));
}

inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}

inline void io_wait(void) { outb(0x80, 0); }

inline void cli(void) { __asm__ volatile("cli"); }

inline void sti(void) { __asm__ volatile("sti"); }