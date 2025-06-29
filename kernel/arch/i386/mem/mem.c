#include "mem.h"
#include "gdt.h"
#include <kernel/mem.h>

void __initMem() {
  initGdt();
  initPaging();
}
