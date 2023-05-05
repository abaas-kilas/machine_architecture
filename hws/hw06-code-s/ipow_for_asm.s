### Annotated version of assembly from ipow_for.c
	.file	"ipow_for.c"
	.text
	.globl	ipow
	.type	ipow, @function
ipow:                           # entry for the ipow function
.LFB0:                          # %edi is base, %esi is exp
	.cfi_startproc
	movl	$0, %edx        # edx is i=0
	movl	$1, %eax        # eax is pow=1
	jmp	.L2
.L3:
	imull	%edi, %eax      # pow = pow * base
	addl	$1, %edx        # i++
.L2:
	cmpl	%esi, %edx      # for() loop top: i < exp
	jl	.L3             # do loop
	rep ret
	.cfi_endproc
.LFE0:
	.size	ipow, .-ipow
	.ident	"GCC: (GNU) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
