#include "page.h"
#include <kernel/defs.h>
#include <kernel/mem.h>
#include <stdint.h>

pageframe_t startFrame;
uint32_t *directory, bitmap[MAX_PAGES / 32 + 1];

static inline void useFrame(uint32_t idx) {
  bitmap[idx / 32] |= (1 << (idx % 32));
}

static inline void unuseFrame(uint32_t idx) {
  bitmap[idx / 32] &= ~(1 << (idx % 32));
}

static inline uint32_t usedFrame(uint32_t idx) {
  return bitmap[idx / 32] & (1 << (idx % 32));
}

static pageframe_t __kallocFrame() {
  uint32_t page = startFrame / PAGE_SIZE;
  for (; usedFrame(page); ++page) {
    if (page == MAX_PAGES) {
      return NO_AVAIL_PAGE;
    }
  }
  // todo : set present bit

  //  for (uint32_t i = 0; i < N_PAGE_ENTRY; ++i) {
  //    if (!(directory[i] & PRESENT)) {
  //      continue;
  //    }

  //    uint32_t *table = (uint32_t *)(directory[i] - directory[i] % PAGE_SIZE);
  //    for (uint32_t l = 0; l < N_PAGE_ENTRY; ++l) {
  //      if (!(table[l] & PRESENT)) {
  //        continue;
  //      }

  //    }
  //  }

  return (page * PAGE_SIZE);
}

static void __kfreeFrame(pageframe_t addr) { uint32_t idx = addr / PAGE_SIZE; }

uint32_t kallocFrame() { return __kallocFrame(); }

void kfreeFrame(uint32_t addr) { __kfreeFrame((pageframe_t)addr); }

static void setStartFrame(ptr_t ptr) {
  startFrame = (ptr / PAGE_SIZE + 1) * PAGE_SIZE;
}

static inline void initBitMap() {
  for (uint32_t idx = 0; idx < MAX_PAGES; ++idx) {
    unuseFrame(idx);
  }
}

void initPaging() {
  // get where to start
  setStartFrame(&endkernel);
  initBitMap();

  // make page directory (directory dwells on first page)
  directory = (uint32_t *)startFrame;
  for (uint32_t i = 0; i < N_PAGE_ENTRY; ++i) {
    directory[i] = RW;
  }

  // make first page tables(first table dwells on second page)
  uint32_t *firstTable = (uint32_t *)((ptr_t)startFrame + PAGE_SIZE), p;
  for (uint32_t i = 0; i < N_PAGE_ENTRY; ++i) {
    firstTable[i] = (i * PAGE_SIZE) | RW;
    if (i * PAGE_SIZE <= (uint32_t)firstTable) {
      firstTable[i] |= PRESENT;
      useFrame(i);
    }
  }
  directory[0] = ((uint32_t)firstTable) | RW | PRESENT;

  // set register to enable paging
  setPageRegs(directory);

  printf("%p %p ", directory, firstTable);
}
