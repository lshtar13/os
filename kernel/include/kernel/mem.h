#ifndef _KERNEL_MEM_H
#define _KERNEL_MEM_H 1

#include "defs.h"
#include <stdint.h>

void initMem();
void initPaging(void);
void setPageRegs(ptr_t);

ptr_t kallocFrame();
void kfreeFrame(ptr_t addr);
#endif