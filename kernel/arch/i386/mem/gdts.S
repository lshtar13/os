.global gdt_flush

gdt_flush:
	movl 4(%esp), %eax
	lgdtl (%eax)
    
	movl $0x10, %eax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	jmpl $0x08, $reload_cs
reload_cs:

	ret

