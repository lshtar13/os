.global idt_flush
idt_flush:
	movl 4(%esp), %eax
	lidtl (%eax)
	sti
	ret

isr_common_stub:
	# 1. Save CPU state
	pusha 
	movw %ax, %ds 
	push %eax 
	movw %ax, 0x10
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	
    # 2. Call C handler
	call isr_handler
	
    # 3. Restore state
	pop %eax 
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	popa
	add %esp, 8 
	sti
	iret 

.macro isr_stub num
.global isr\num
isr\num:
    cli
	push $0
	push $\num
    jmp isr_common_stub
.endm

.extern isr_handler
isr_stub 0
isr_stub 1
isr_stub 2
isr_stub 3
isr_stub 4
isr_stub 5
isr_stub 6
isr_stub 7
isr_stub 8
isr_stub 9
isr_stub 10
isr_stub 11
isr_stub 12
isr_stub 13
isr_stub 14
isr_stub 15
isr_stub 16
isr_stub 17
isr_stub 18
isr_stub 19
isr_stub 20
isr_stub 21
isr_stub 22
isr_stub 23
isr_stub 24
isr_stub 25
isr_stub 26
isr_stub 27
isr_stub 28
isr_stub 29
isr_stub 30
isr_stub 31
isr_stub 32
