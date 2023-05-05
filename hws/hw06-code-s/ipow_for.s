	.file	"ipow_for.c"
# GNU C17 (GCC) version 10.2.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 10.2.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.21-GMP

# warning: MPFR header version 4.0.2 differs from library version 4.1.0.
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  ipow_for.c -mtune=generic -march=x86-64 -Og
# -fverbose-asm
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fallocation-dce -fasynchronous-unwind-tables -fauto-inc-dec
# -fcombine-stack-adjustments -fcompare-elim -fcprop-registers -fdefer-pop
# -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-symbols -feliminate-unused-debug-types
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm
# -fgnu-unique -fguess-branch-probability -fident -finline -finline-atomics
# -fipa-profile -fipa-pure-const -fipa-reference
# -fipa-reference-addressable -fipa-stack-alignment -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -flifetime-dse -fmath-errno
# -fmerge-constants -fmerge-debug-strings -fomit-frame-pointer -fpeephole
# -fplt -fprefetch-loop-arrays -freg-struct-return -freorder-blocks
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop
# -fstack-protector-strong -fstdarg-opt -fstrict-volatile-bitfields
# -fsync-libcalls -ftoplevel-reorder -ftrapping-math
# -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
# -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
# -ftree-forwprop -ftree-fre -ftree-loop-if-convert -ftree-loop-im
# -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
# -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
# -ftree-ter -funit-at-a-time -funwind-tables -fverbose-asm
# -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	ipow
	.type	ipow, @function
ipow:
.LFB0:
	.cfi_startproc
# ipow_for.c:3:   for(int i=0; i<exp; i++){
	movl	$0, %eax	#, i
# ipow_for.c:2:   int pow = 1;
	movl	$1, %edx	#, <retval>
# ipow_for.c:3:   for(int i=0; i<exp; i++){
	jmp	.L2	#
.L3:
# ipow_for.c:4:     pow = pow * base;
	imull	%edi, %edx	# base, <retval>
# ipow_for.c:3:   for(int i=0; i<exp; i++){
	addl	$1, %eax	#, i
.L2:
# ipow_for.c:3:   for(int i=0; i<exp; i++){
	cmpl	%esi, %eax	# exp, i
	jl	.L3	#,
# ipow_for.c:7: }
	movl	%edx, %eax	# <retval>,
	ret	
	.cfi_endproc
.LFE0:
	.size	ipow, .-ipow
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
