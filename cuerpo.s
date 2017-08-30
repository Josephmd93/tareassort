.section .data

.section .text

.globl power
.globl _start

_start:

pushl $3
pushl $2
call power
addl $8, %esp

pushl %eax
pushl $2
pushl $5
call power
addl $8, %esp

popl %ebx
addl %eax, %ebx
movl $1, %eax
int $0x80

