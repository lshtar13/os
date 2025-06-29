# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a multiboot header that marks the program as a kernel.
.section .multiboot.data, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate the initial stack.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# Preallocate pages used for paging. Don't hard-code addresses and assume they
# are available, as the bootloader might have loaded its multiboot structures or
# modules there. This lets the bootloader know it must avoid the addresses.
.section .bss, "aw", @nobits
.global boot_page_directory
.global boot_page_table1 
.global swap_page_table0
.global swap_page_table1
	.align 4096
boot_page_directory:
	.skip 4096
boot_page_table1:
	.skip 4096
swap_page_table0:
	.skip 4096
swap_page_table1:
	.skip 4096
# Further page tables may be required if the kernel grows beyond 3 MiB.

# The kernel entry point.
.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:
	# set page table (kernel)
	movl $(boot_page_table1 - 0xC0000000), %edi
	movl $0, %esi
	movl $1023, %ecx

1:
	# map only kernel codes 
	cmpl $startkernel, %esi
	jl 2f

	# mapping done
	cmpl $(endkernel - 0xC0000000), %esi
	jge 3f

	# set table 
	# esi => physical address
	movl %esi, %edx
	# flags (present)
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	# next page
	addl $4096, %esi
	addl $4, %edi
	loop 1b

3:
	# VGA text buffer
	movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 * 4

	# sharing page table between identity paging and higher half
	# identity paging
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	# higher half
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

	# set register(page directory)
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# enable paging
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# jump to higher half
	lea 4f, %ecx
	jmp *%ecx

.section .text

4:
	# erase identity paging
	movl $0, boot_page_directory + 0

	# flush tlb cache 
	movl %cr3, %ecx
	movl %ecx, %cr3

	mov $stack_top, %esp

	call kernel_main

	cli
1:	hlt
	jmp 1b