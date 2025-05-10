#include <kernel/defs.h>
#include <kernel/mem.h>

extern void loadPageDirectory(ptr_t);
extern void enablePaging();

static ptr_t directory;

void setPageRegs(ptr_t addr) {
  directory = addr;
  loadPageDirectory(directory);
  enablePaging();
}

void flushPageRegs() { loadPageDirectory(directory); }