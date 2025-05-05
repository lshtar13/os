#include <stdint.h>
#ifndef __KERNEL_PAGE_H_
#define __KERNEL_PAGE_H_ 1

#include <kernel/defs.h>

#define PAGE_SIZE 0x1000
#define MAX_PAGES 0x100000
#define N_PAGE_ENTRY 0x400
#define NO_AVAIL_PAGE 0

#define DIDX(addr) (addr >> 22)
#define TIDX(addr) ((addr >> 12) & 0xFFF)
#define ADDR(entry) (entry & ~0xFFF)

#define SUP 0x4
#define RW 0x2
#define PRESENT 0x1

extern ptr_t endkernel;

typedef ptr_t pageframe_t;

#endif