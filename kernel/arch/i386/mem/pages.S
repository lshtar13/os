.global loadPageDirectory
loadPageDirectory:
pushl %ebp
movl %esp, %ebp
movl 8(%esp), %eax
movl %eax, %cr3
movl %ebp, %esp
popl %ebp
ret

.global enablePaging
enablePaging:
pushl %ebp
movl %esp, %ebp
movl %cr0, %eax
or $0x80000000, %eax
movl %eax, %cr0
movl %ebp, %esp
popl %ebp
ret

.global disablePaging
disablePaging:
pushl %ebp
movl %esp, %ebp
movl %cr0, %eax
xor $0x80000000, %eax
movl %eax, %cr0
movl %ebp, %esp
popl %ebp
ret