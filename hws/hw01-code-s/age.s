	.file	"age.c"
	.text
	.section	.rodata
.LC0:
	.string	"Enter your age in years: "
.LC1:
	.string	"%d"
.LC2:
	.string	"You are %d minutes old.\n"
	.align 8
.LC3:
	.string	"You're too young to anything fun."
	.align 8
.LC4:
	.string	"You can vote but cannot legally imbibe alcohol."
	.align 8
.LC5:
	.string	"I bet that hasn't stopped you from trying though..."
	.align 8
.LC6:
	.string	"You may imbibe alcohol but cannot be president"
	.align 8
.LC7:
	.string	"You can vote, drink, and be president.\nTry all three at once!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -16(%rbp)
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-16(%rbp), %eax
	imull	$525600, %eax, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	cmpl	$17, %eax
	jg	.L2
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	jmp	.L3
.L2:
	movl	-16(%rbp), %eax
	cmpl	$17, %eax
	jle	.L4
	movl	-16(%rbp), %eax
	cmpl	$20, %eax
	jg	.L4
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	jmp	.L3
.L4:
	movl	-16(%rbp), %eax
	cmpl	$20, %eax
	jle	.L5
	leaq	.LC6(%rip), %rdi
	call	puts@PLT
	jmp	.L3
.L5:
	leaq	.LC7(%rip), %rdi
	call	puts@PLT
.L3:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
