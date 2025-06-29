#ifndef __INCLUDE_KERNEL_MEM_H
#define __INCLUDE_KERNEL_MEM_H 1

#include <stdint.h>

#define KERNEL_START 0xC0000000
#define PAGE_DICT 0xD03FF000
#define PAGE_TABLE_BASE 0xD0000000

#define __PAGE_TABLE(vaddr)                                                    \
  ((uint32_t)PAGE_TABLE_BASE + (PAGE_TIDX(vaddr) << 12))

extern uint32_t startkernel, endkernel;

void __initMem();
void initMem();

void initFrames(uint32_t ptr);
uint32_t kallocFrame();
void kfreeFrame(uint32_t addr);

void __initPaging();
void initPaging();
void setPageRegs(uint32_t);
void flushPageRegs();

uint32_t __allocPage();
uint32_t kallocPage(uint32_t addr);

void __freePage(uint32_t vaddr);
void kfreePage(uint32_t vaddr);

#endif