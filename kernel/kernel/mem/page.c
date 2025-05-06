#include "page.h"
#include <kernel/defs.h>
#include <kernel/mem.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct pframe_t frames;
uint32_t *directory, bitmap[N_BITMAP_ENTRY] = {};

static inline void useFrame(uint32_t idx) {
  frames.bitmap[idx / 32] |= (1 << idx % 32);
}

static inline void unuseFrame(uint32_t idx) {
  frames.bitmap[idx / 32] &= ~(1 << (idx % 32));
}

static inline uint32_t isusedFrame(uint32_t idx) {
  return frames.bitmap[idx / 32] & (1 << (idx % 32));
}

static uint32_t allocFrame() {
  uint32_t fidx = frames.lastIdx;
  for (; isusedFrame(fidx); ++fidx) {
    if (fidx == MAX_FRAMES) {
      return NO_AVAIL_FRAME;
    }
  }

  useFrame(fidx);
  frames.lastIdx = fidx;

  return fidx * FRAME_SIZE;
}

static pageframe_t __kallocPage() {
  uint32_t frame = allocFrame(), addr = frame;

  uint32_t tidx = PAGE_TIDX(addr), pidx = PAGE_PIDX(addr);
  directory[tidx] |= PAGE_PRESENT;

  uint32_t *table = (uint32_t *)PAGE_ADDR(directory[tidx]);
  table[pidx] = frame | PAGE_RW | PAGE_PRESENT;

  return addr;
}

uint32_t kallocPage() { return __kallocPage(); }

static void initFrames(uint32_t ptr) {
  frames.start = (ptr / FRAME_SIZE + 1) * FRAME_SIZE;
  memset(bitmap, 0, sizeof(uint32_t) * N_BITMAP_ENTRY);
}

void initPaging() {
  initFrames(&endkernel);

  // make page directory (directory dwells on first page)
  directory = (uint32_t *)frames.start;
  for (uint32_t i = 0; i < N_PAGE_ENTRY; ++i) {
    directory[i] = PAGE_RW;
  }

  // make first page tables(first table dwells on second page)
  // pagetable의 frame들은 첫번째 pagetable에 mapping한다.
  uint32_t *firstTable = (uint32_t *)(frames.start + FRAME_SIZE),
           *lastTable = (uint32_t *)(frames.start + FRAME_SIZE * N_PAGE_ENTRY);
  for (uint32_t fidx = 0; fidx * FRAME_SIZE <= (uint32_t)lastTable; ++fidx) {
    firstTable[fidx] = (fidx * FRAME_SIZE) | PAGE_RW | PAGE_PRESENT;
    useFrame(fidx);
  }

  for (uint32_t i = 0; i <= N_PAGE_ENTRY; ++i) {
    directory[i] = ((uint32_t)firstTable + FRAME_SIZE * i) | PAGE_RW;
  }
  directory[0] |= PAGE_PRESENT;
  directory[1] |= PAGE_PRESENT;

  // set register to enable paging
  setPageRegs(directory);
  printf("%p %p ", firstTable, lastTable);
}
