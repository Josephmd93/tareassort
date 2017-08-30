.section .data

.section .text

.globl power

power:
pushl %ebp
movl %esp, %ebp
subl $4, %esp

movl 8(%ebp), %ebx
movl 12(%ebp), %ecx
movl %ebx, -4(%ebp)

power_loop_start:
cmpl $1, %ecx
je end_power
movl -4(%ebp), %eax
imull %ebx, %eax
movl %eax, -4(%ebp)
decl %ecx
jmp power_loop_start

end_power:
movl -4(%ebp), %eax
movl %ebp, %esp
popl %ebp
ret

