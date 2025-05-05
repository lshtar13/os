#include <kernel/defs.h>
#include <kernel/mem.h>

extern void loadPageDirectory(ptr_t);
extern void enablePaging();

void setPageRegs(ptr_t directory) {
  loadPageDirectory(directory);
  enablePaging();
}