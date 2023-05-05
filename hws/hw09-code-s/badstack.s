	.file	"badstack.c"
	.text
	.globl	inc_larger
	.type	inc_larger, @function
inc_larger:
.LFB12:
	.cfi_startproc
	movl	(%rdi), %edx
	movl	(%rsi), %eax
	cmpl	%eax, %edx
	jl	.L2
	addl	$1, %edx
	movl	%edx, (%rdi)
	ret
.L2:
	addl	$1, %eax
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE12:
	.size	inc_larger, .-inc_larger
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"%d, %d, %d, %d, who do we appreciate?\n"
	.align 8
.LC1:
	.string	"Compilers! Compilers! Yeeeeaaah COMPILERS!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movl	$2, 8(%rsp)
	movl	$3, 12(%rsp)
	movl	$6, 16(%rsp)
	movl	$7, 20(%rsp)
	leaq	12(%rsp), %rsi
	leaq	8(%rsp), %rdi
	call	inc_larger
	leaq	20(%rsp), %rsi
	leaq	16(%rsp), %rdi
	call	inc_larger
	movl	20(%rsp), %r8d
	movl	16(%rsp), %ecx
	movl	12(%rsp), %edx
	movl	8(%rsp), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L7
	movl	$0, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
