.text
.globl	set_coins
set_coins:
### args are
### %edi = int cents
### %rsi = coints_t *coins
	## BLOCK A
	cmpl	$99,%edi        # Describe this block
	jg      .OOB
	cmpl    $0,%edi
	jl	.OOB
	
	## BLOCK B
	movl    %edi,%eax       # eax now has cents
        cqto                    # prep for division
	movl    $25,%r8d
        idivl   %r8d
        movb    %al,0(%rsi)     # coins->quarters = cents / 25
	movl    %edx,%eax       # cents = cents % 25
	
	cqto                    # prep for division
        movl    $10,%r8d
        idivl   %r8d
        movb    %al,1(%rsi)     # coins->dimes = cents / 10
	movl    %edx,%eax       # cents = cents % 10
	
        ## BLOCK C: Complete for nickels and pennies
	cqto                    # prep for division
        movl    $5,%r8d
        idivl   %r8d
        movb    %al,2(%rsi)     # coins->nickels = cents / 5
	movb    %dl,3(%rsi)     # coins->pennies = cents % 5

        ## Return
	movl    $0,%eax         # return value
        ret
.OOB:
	movl	$1, %eax
	ret


.globl	total_coins
total_coins:
### args are
### %rdi packed coin_t struct with struct fields in the following bit rangs
###  {0-7: quarters, 8-15: dimes, 16-23-: nickels,  24-31: pennies}
	movl    $0,%eax          # tot = 0
	
	movq    %rdi,%rdx        # extract quarters
	## sarq    $0,%rdx         # no shift needed
        andq    $0xFF,%rdx       # rdx = quarters, mask low byte
        imul    $25,%edx         # rdx *= 25
        addl    %edx,%eax        # tot += coins.quarters*25
	
	movq    %rdi,%rdx        # extract dimes
	sarq    $8,%rdx          # move dimes to low order bits
        andq    $0xFF,%rdx       # rdx = dimes
        imul    $10,%edx         # rdx *= 10
        addl    %edx,%eax        # tot += coins.dimes*10
	
	## BLOCK D: add on nickels and then pennies
	## Nickels
	movq    %rdi,%rdx        # extract nickels
	sarq    $16,%rdx         # move nickels to low order bits
        andq    $0xFF,%rdx       # rdx = nickels
        imul    $5,%edx          # rdx *= 5
        addl    %edx,%eax        # tot += coins.nickels*5
        
	## Pennies
	movq    %rdi,%rdx        # extract pennies
	sarq    $24,%rdx         # move pennies to low order bits
        andq    $0xFF,%rdx       # rdx = pennies
        ## imul    $1,%edx         # rdx *= 1
        addl    %edx,%eax        # tot += coins.pennies

	## return value already in eax
        ret
