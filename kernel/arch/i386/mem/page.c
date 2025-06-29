#include "page.h"
#include <kernel/mem.h>
#include <stdint.h>

static uint32_t *directory, *tables;

void setPageRegs(uint32_t addr) {
  directory = (uint32_t *)addr;
  loadPageDirectory((uint32_t)directory);
  enablePaging();
}

uint32_t __allocPage(uint32_t vaddr) {
  __mapPage(kallocFrame(), vaddr);
  return vaddr;
}

void __freePage(uint32_t addr) {
  uint32_t *table = (uint32_t *)__PAGE_TABLE(addr);
  table[PAGE_PIDX(addr)] ^= PAGE_PRESENT;
  loadPageDirectory((uint32_t)boot_page_directory - KERNEL_START);
}

void __mapPage(uint32_t frame, uint32_t addr) {
  uint32_t *table = (uint32_t *)__PAGE_TABLE(addr);
  if (!(tables[PAGE_TIDX(addr)] & PAGE_PRESENT)) {
    tables[PAGE_TIDX(addr)] = directory[PAGE_TIDX(addr)] =
        kallocFrame() | PAGE_RW | PAGE_PRESENT;
    loadPageDirectory((uint32_t)boot_page_directory - KERNEL_START);
  }

  table[PAGE_PIDX(addr)] = frame | PAGE_RW | PAGE_PRESENT;
  loadPageDirectory((uint32_t)boot_page_directory - KERNEL_START);
}

void __initPaging() {
  // tables ==> table page들의 table (swap0)
  directory = boot_page_directory;
  directory[PAGE_TIDX(PAGE_TABLE_BASE)] =
      PAGE_PADDR((uint32_t)swap_page_table0 - KERNEL_START) | PAGE_RW |
      PAGE_PRESENT;
  swap_page_table0[PAGE_TIDX(PAGE_TABLE_BASE)] =
      PAGE_PADDR((uint32_t)swap_page_table0 - KERNEL_START) | PAGE_RW |
      PAGE_PRESENT;

  loadPageDirectory((uint32_t)boot_page_directory - KERNEL_START);

  tables = __PAGE_TABLE(PAGE_TABLE_BASE);
  tables[PAGE_TIDX(KERNEL_START)] =
      PAGE_PADDR((uint32_t)boot_page_table1 - KERNEL_START) | PAGE_RW |
      PAGE_PRESENT;
  tables[PAGE_PIDX(PAGE_DICT)] =
      PAGE_PADDR((uint32_t)boot_page_directory - KERNEL_START) | PAGE_RW |
      PAGE_PRESENT;

  loadPageDirectory((uint32_t)boot_page_directory - KERNEL_START);
}