#ifndef _KERNEL_MEM_H
#define _KERNEL_MEM_H 1

#include "defs.h"
#include <stdint.h>

void initMem();

void initPaging(void);
void setPageRegs(ptr_t);
void flushPageRegs();
uint32_t kallocPage();
void kfreePage(uint32_t vaddr);

ptr_t kallocFrame();
void kfreeFrame(ptr_t addr);
#endif