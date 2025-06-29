#ifndef _ARCH_I386_PAGE_H
#define _ARCH_I386_PAGE_H

#include <kernel/mem.h>
#include <stdint.h>

#define N_PAGE_ENTRY 0x400
#define N_TABLE_ENTRY 0x3FF
#define PAGE_TIDX(addr) ((uint32_t)addr >> 22)
#define PAGE_PIDX(addr) (((uint32_t)addr >> 12) & 0x3FF)
#define PAGE_2_ADDR(tidx, pidx)                                                \
  (((uint32_t)tidx << 22) | ((uint32_t)pidx << 12))
#define PAGE_PADDR(entry) ((uint32_t)entry & ~0xFFF)

#define PAGE_TABLE_TIDX 1
#define PAGE_TABLE_PIDX(tidx) (tidx + 1)

#define PAGE_SUP 0x4
#define PAGE_RW 0x2
#define PAGE_PRESENT 0x1

extern uint32_t boot_page_directory[N_TABLE_ENTRY],
    boot_page_table1[N_PAGE_ENTRY], swap_page_table0[N_PAGE_ENTRY],
    swap_page_table1[N_PAGE_ENTRY];

extern void loadPageDirectory(uint32_t);
extern void enablePaging();
extern void disablePaging();

#endif
