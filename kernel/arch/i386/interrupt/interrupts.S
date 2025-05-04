.global idt_flush
idt_flush:
	movl 4(%esp), %eax
	lidtl (%eax)
	sti
	ret

isr_common_stub:
    pushal                  
    movw %ds, %ax         
    pushl %eax            
    movl %cr2, %eax       
    pushl %eax            

    movw $0x10, %ax       
    movw %ax, %ds         
    movw %ax, %es         
    movw %ax, %fs         
    movw %ax, %gs         

    pushl %esp            
    call exception_handler

    addl $0x8, %esp       
    popl %ebx              
    movw %bx, %ds           
    movw %bx, %es           
    movw %bx, %fs           
    movw %bx, %gs           

    popal                   
	addl $0x8, %esp
	sti
	iret 

.macro isr_stub num
.global isr\num
isr\num:
    cli
	pushl $0
	pushl $\num
    jmp isr_common_stub
.endm

.extern exception_handler
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
