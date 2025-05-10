#include <stdint.h>
#ifndef __KERNEL_PAGE_H_
#define __KERNEL_PAGE_H_ 1

#include <kernel/defs.h>

#define FRAME_SIZE 0x1000
#define MAX_FRAMES 0x100000
#define N_BITMAP_ENTRY (MAX_FRAMES / 32 + 1)
#define NO_AVAIL_FRAME 0

#define FRAME_USE(bitmap, idx) (bitmap[idx / 32] |= (1 << idx % 32))
#define FRAME_UNUSE(bitmap, idx) (bitmap[idx / 32] &= ~(1 << (idx % 32)))
#define FRAME_ISUSED(bitmap, idx) (bitmap[idx / 32] & (1 << (idx % 32)))

#define N_PAGE_ENTRY 0x400
#define N_TABLE_ENTRY 0x400

#define PAGE_TIDX(addr) (addr >> 22)
#define PAGE_PIDX(addr) ((addr >> 12) & 0x3FF)
#define PAGE_2_ADDR(tidx, pidx) ((tidx << 22) | (pidx << 12))
#define PAGE_PADDR(entry) (entry & ~0xFFF)

#define PAGE_TABLE_TIDX 1
#define PAGE_TABLE_PIDX(tidx) (tidx + 1)

#define PAGE_SUP 0x4
#define PAGE_RW 0x2
#define PAGE_PRESENT 0x1

extern ptr_t endkernel;

typedef ptr_t pageframe_t;

struct pframe_t {
  ptr_t start;
  uint32_t bitmap[N_BITMAP_ENTRY], lastIdx;
};

typedef struct Page_Directory_Entry {
	
  char addrLo;
  uint16_t addrHi;
} PDE;

#endif