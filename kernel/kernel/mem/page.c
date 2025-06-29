#include "page.h"
#include <kernel/mem.h>
#include <stdint.h>

uint32_t kallocPage(uint32_t addr) { return __allocPage(addr); }

void kfreePage(uint32_t vaddr) { __freePage(vaddr); }

void initPaging() { __initPaging(); }