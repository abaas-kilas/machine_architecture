## int posneg(int *ptr);
## // Determines if pointer to given int has a positive or
## // negative value. Returns 0 for positive, 1 for negative.
## // Defined in posneg.s assembly file.

.text
.global posneg
posneg:
        movl    (%rdi),%esi     # move 32-bit quantity
        cmpl    $0,%esi         # compare 32-bit quantity
        jl      .NEG
        movl    $0,%eax
        ret
.NEG:
        movl    $1,%eax
        ret

