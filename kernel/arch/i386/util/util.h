#ifndef __ARCH_I386_UTIL_H
#define __ARCH_I386_UTIL_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);
void cli(void);
void sti(void);
#endif