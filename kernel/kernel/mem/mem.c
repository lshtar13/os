#include <kernel/mem.h>
#include <stdint.h>

void initMem() {
  initFrames((uint32_t)&endkernel - KERNEL_START);
  __initMem();
}