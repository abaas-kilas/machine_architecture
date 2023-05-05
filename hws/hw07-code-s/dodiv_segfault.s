### dodiv_segfault.s: provides a division function which computes 
### both quotient and remainder.
### 
### This version has a memory problem in it which
### leads to a segmentation fault.
### 
### int dodiv(int numer, int denom, int *quot, int *rem);        
### args:         1:edi      2:esi       3:rdx     4:rcx
	.text
	.global	dodiv
dodiv:
	cmpl $0,%edi            # compare arg1 to 0
        je .ERROR_ZERO

        movl %edi,%eax          # copy arg1 to eax for division
        cqto                    # set up division by copy to edx
        idivl %esi              # divide by arg2, eax has quot, edx has rem
        movl %eax,(%rdx)        # write quot to arg3
        movl %edx,(%rcx)        # write rem  to arg4
        movl $0,%eax            # return 0 on success
	ret                     
	
.ERROR_ZERO:
        movl $1,%eax            # return 1 on failure
        ret

## > gcc -g dodiv_main.c dodiv_segfault.s
## > ./a.out
## Segmentation fault (core dumped)
## > valgrind ./a.out
## ==4082== Memcheck, a memory error detector
## ==4082== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
## ==4082== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
## ==4082== Command: ./a.out
## ==4082== 
## ==4082== Invalid write of size 4
## ==4082==    at 0x1091CE: ??? (dodiv_segfault.s:12)
## ==4082==    by 0x489DCE2: (below main) (in /usr/lib/libc-2.29.so)
## ==4082==  Address 0x9 is not stack'd, malloc'd or (recently) free'd
## ==4082== 
## ==4082== 
## ==4082== Process terminating with default action of signal 11 (SIGSEGV): dumping core
## ==4082==  Access not within mapped region at address 0x9
## ==4082==    at 0x1091CE: ??? (dodiv_segfault.s:12)
## ==4082==    by 0x489DCE2: (below main) (in /usr/lib/libc-2.29.so)
## ==4082==  If you believe this happened as a result of a stack
## ==4082==  overflow in your program's main thread (unlikely but
## ==4082==  possible), you can try to increase the size of the
## ==4082==  main thread stack using the --main-stacksize= flag.
## ==4082==  The main thread stack size used in this run was 10022912.
## ==4082== 
## ==4082== HEAP SUMMARY:
## ==4082==     in use at exit: 0 bytes in 0 blocks
## ==4082==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
## ==4082== 
## ==4082== All heap blocks were freed -- no leaks are possible
## ==4082== 
## ==4082== For counts of detected and suppressed errors, rerun with: -v
## ==4082== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
## Segmentation fault (core dumped)
        
