#include "page.h"
#include <kernel/defs.h>
#include <kernel/mem.h>
#include <stdint.h>
#include <string.h>

static struct pframe_t frames;
static uint32_t *directory, *tables, nextAddr;

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

static void freeFrame(uint32_t paddr) {
  uint32_t fidx = paddr / FRAME_SIZE;
  unuseFrame(fidx);
  frames.lastIdx = fidx;
}

static pageframe_t __allocPage(uint32_t vaddr) {
  uint32_t tidx = PAGE_TIDX(vaddr), pidx = PAGE_PIDX(vaddr), *table;
  if (!(directory[tidx] & PAGE_PRESENT)) {
    uint32_t tframe = allocFrame();
    directory[tidx] = tframe | PAGE_RW | PAGE_PRESENT;
    tables[tidx + 1] = tframe | PAGE_RW | PAGE_PRESENT;
  }

  table = (uint32_t *)PAGE_2_ADDR(PAGE_TABLE_TIDX, PAGE_TABLE_PIDX(tidx));
  table[pidx] = allocFrame() | PAGE_RW | PAGE_PRESENT;

  printf("table : %p %x ", table, table[pidx]);

  return vaddr;
}

static void __freePage(uint32_t vaddr) {
  uint32_t tidx = PAGE_TIDX(vaddr), pidx = PAGE_PIDX(vaddr), *table, paddr;
  table = (uint32_t *)PAGE_2_ADDR(PAGE_TABLE_TIDX, PAGE_TABLE_PIDX(tidx));
  table[pidx] = table[pidx] & ~PAGE_PRESENT;
  paddr = PAGE_PADDR(table[pidx]);
  freeFrame(paddr);

  printf("table : %p %x ", table, table[pidx]);
  flushPageRegs();
}

uint32_t kallocPage() {
  uint32_t result = __allocPage(nextAddr);
  nextAddr += FRAME_SIZE;
  return result;
}

void kfreePage(uint32_t vaddr) { __freePage(vaddr); }

static void initFrames(uint32_t ptr) {
  frames.start = (ptr / FRAME_SIZE + 1) * FRAME_SIZE;
  for (uint32_t fidx = 0; fidx * FRAME_SIZE <= frames.start; ++fidx) {
    useFrame(fidx);
    frames.lastIdx = fidx;
  }

  memset(frames.bitmap, 0, sizeof(uint32_t) * N_BITMAP_ENTRY);
}

void initPaging() {
  initFrames(&endkernel);

  // make page directory (directory dwells on first page)
  uint32_t *dict = (uint32_t *)allocFrame();
  for (uint32_t i = 0; i < N_TABLE_ENTRY; ++i) {
    dict[i] = PAGE_RW;
  }

  // make first page tables(first table dwells on second page)
  // pagetable의 frame들은 두번째 pagetable에 mapping한다.
  // 0번째 table => kernel
  // 1번째 table => table info
  uint32_t *firstTable = (uint32_t *)allocFrame(),
           *secondTable = (uint32_t *)allocFrame();
  memset(firstTable, 0, sizeof(uint32_t) * N_PAGE_ENTRY);
  memset(secondTable, 0, sizeof(uint32_t) * N_PAGE_ENTRY);

  // kernel pages
  dict[0] = PAGE_PADDR((uint32_t)firstTable) | PAGE_RW | PAGE_PRESENT;
  for (uint32_t addr = 0; addr <= (uint32_t)frames.start; addr += FRAME_SIZE) {
    firstTable[PAGE_PIDX(addr)] = PAGE_PADDR(addr) | PAGE_RW | PAGE_PRESENT;
  }

  // table pages
  tables = secondTable;
  dict[1] = PAGE_PADDR((uint32_t)secondTable) | PAGE_RW | PAGE_PRESENT;
  secondTable[0] = PAGE_PADDR((uint32_t)dict) | PAGE_RW | PAGE_PRESENT;
  secondTable[1] = PAGE_PADDR((uint32_t)firstTable) | PAGE_RW | PAGE_PRESENT;
  secondTable[2] = PAGE_PADDR((uint32_t)secondTable) | PAGE_RW | PAGE_PRESENT;
  // set register to enable paging
  setPageRegs(dict);
  directory = (uint32_t *)PAGE_2_ADDR(1, 0);
  tables = (uint32_t *)PAGE_2_ADDR(1, 2);
  nextAddr = PAGE_2_ADDR(2, 0);
}
