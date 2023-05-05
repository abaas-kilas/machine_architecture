	.file	"quote_data.c"
	.text
	.globl	max_size
	.type	max_size, @function
max_size:
.LFB11:
	.cfi_startproc
	movq	choices(%rip), %rax
	movl	8(%rax), %eax
	ret
	.cfi_endproc
.LFE11:
	.size	max_size, .-max_size
	.globl	list_get
	.type	list_get, @function
list_get:
.LFB12:
	.cfi_startproc
	movq	%rdi, %rax
	movl	%esi, %edi
	testl	%esi, %esi
	js	.L6
	cmpl	%esi, 8(%rax)
	jle	.L7
	movq	(%rax), %rax
	movl	$0, %edx
	jmp	.L4
.L5:
	addl	$1, %edx
	movq	256(%rax), %rax
.L4:
	testq	%rax, %rax
	setne	%sil
	cmpl	%edi, %edx
	setne	%cl
	testb	%cl, %sil
	jne	.L5
	ret
.L6:
	movl	$0, %eax
	ret
.L7:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	list_get, .-list_get
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Out of bounds"
	.text
	.globl	get_it
	.type	get_it, @function
get_it:
.LFB13:
	.cfi_startproc
	movl	%edi, %esi
	movq	choices(%rip), %rdi
	call	list_get
	testq	%rax, %rax
	je	.L11
.L8:
	ret
.L11:
	leaq	.LC0(%rip), %rax
	jmp	.L8
	.cfi_endproc
.LFE13:
	.size	get_it, .-get_it
	.globl	choices
	.section	.data.rel.local,"aw"
	.align 8
	.type	choices, @object
	.size	choices, 8
choices:
	.quad	choices_actual
	.globl	choices_actual
	.align 16
	.type	choices_actual, @object
	.size	choices_actual, 16
choices_actual:
	.quad	nodes
	.long	15
	.zero	4
	.globl	nodes
	.align 32
	.type	nodes, @object
	.size	nodes, 3960
nodes:
	.string	"Within C++, there is a much smaller and cleaner language struggling to get out. (It is C.)"
	.zero	165
	.quad	nodes+3432
	.string	"So don't use C."
	.zero	240
	.quad	nodes+528
	.string	"Java prevents you from shooting yourself in the foot by cutting off all your fingers."
	.zero	170
	.quad	nodes+2112
	.string	"C++ makes it harder, but when you do, it blows away your whole leg."
	.zero	188
	.quad	nodes+264
	.string	"This is why most programmers are such poor dancers."
	.zero	204
	.quad	nodes+1320
	.string	"When Dennis Ritchi discovered this, he immediately bought stock in steel-footed boots."
	.zero	169
	.quad	nodes+2376
	.string	"The only way to do good, efficient, and system-level and portable C++ ends up to limit\nyourself to all the things that are basically available in C."
	.zero	107
	.quad	nodes+792
	.string	"I made up the term \"object-oriented\", and I can tell you I did not have C++ in mind."
	.zero	171
	.quad	0
	.string	"C++ is a language strongly optimized for liars and people who go by guesswork and ignorance."
	.zero	163
	.quad	nodes+2640
	.string	"C++ maintains the original spirit of C, that the programmer not the language is in charge."
	.zero	165
	.quad	nodes+1584
	.string	"C++ is an octopus made by nailing extra legs onto a dog."
	.zero	199
	.quad	nodes+3168
	.string	"But at least you don't need Skynet to compile it which is more than I can say for C++."
	.zero	169
	.quad	nodes+1848
	.string	"When you\342\200\231re programming C++ no one can ever agree on which ten percent of the language is\nsafe to use."
	.zero	151
	.quad	nodes+3696
	.string	"C++ is just an abomination. Everything is wrong with it in every way."
	.zero	186
	.quad	nodes+1056
	.string	"The major cause of complaints is C++'s undoubted success. As someone remarked:\nThere are only two kinds of programming languages: those people always bitch about and those nobody uses."
	.zero	71
	.quad	nodes+2904
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
