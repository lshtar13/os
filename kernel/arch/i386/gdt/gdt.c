#include "gdt.h"
#include <kernel/mem.h>
#include <stdint.h>

extern void gdt_flush(addr_t);

struct gdt_entry gdt_entries[GDT_ENTRY_N];
struct gdt_ptr gdt_ptr;

void initGdt(){
	gdt_ptr.base =(uintptr_t)&gdt_entries;
	gdt_ptr.limit = (sizeof(struct gdt_entry)*GDT_ENTRY_N) -1;
	
	setGdtEntry(0, 0, 0, 0, 0);
	setGdtEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kcode
	setGdtEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kdata
	setGdtEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // ucode
	setGdtEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // udata
	
	gdt_flush(&gdt_ptr);
}

void setGdtEntry(uint32_t idx, uint32_t base, uint32_t limit, uint8_t access,
                 uint8_t gran){
	gdt_entries[idx].base_low = (base & 0xFFFF);
	gdt_entries[idx].base_middle = (base>>16) & 0xFF;
	gdt_entries[idx].base_high = (base >> 24) & 0xFF;

	gdt_entries[idx].limit= (limit & 0xFFFF);
	gdt_entries[idx].flags= (limit>>16) & 0x0F;
	gdt_entries[idx].flags |=(gran&0xF0);

	gdt_entries[idx].access = access;
}

void initMem(){
	initGdt();
}