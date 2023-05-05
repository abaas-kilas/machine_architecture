/*
A lot of my code here is more simplified than my original functions from Project
2. It was all still hand-coded but I changed up parts like finding the negative 
place, when to set the temp fields, etc. Parts of my original functions were just 
too wordy/complex to match exactly so this is just disclaiming those disparities. 
*/



#---------------------------------------------------



.text
.global  set_temp_from_ports
set_temp_from_ports:
    .STFP_START:
        movw    THERMO_SENSOR_PORT(%rip), %dx       # copy sensor to dx
        movb    THERMO_STATUS_PORT(%rip), %cl       # copy status to cl
        cmpw    $64000,%dx
        ja      .ERROR_SENSOR                       # if(THERMO_SENSOR_PORT>64000)
        movb    %dl,%r10b                         
        and     $63,%r10b                           # rem=THERMO_SENSOR_PORT%64
        shr     $6,%dx                              # tem=THERMO_SENSOR_PORT/64
        cmpb    $32,%r10b                         
        jae     .ROUND                              # if(rem>32)
        jmp     .NO_ROUND                           # else
    .ROUND:
        subw     $499,%dx                           # tem=tem-500+1
        jmp     .CHECK_STATUS
    .NO_ROUND:
        subw     $500,%dx                           # tem=tem-500
    .CHECK_STATUS:
        testb   $1,%cl
        jnz     .FAHRENHEIT                         # if(THERMO_STATUS_PORT)
        jmp     .SET_FIELDS                         # else
    .FAHRENHEIT:
        movw    %dx,%ax                             # copy non converted dx to ax
        movl    $9,%r8d
        imul    %r8d                                # tem=tem*9
        cwtl                                    
        cltq                                    
        cqto                                        # div prep
        movl    $5,%r8d
        idiv    %r8d                                # tem=tem/5
        add     $320,%rax                           # tem=tem+320
        movw    %ax,%dx                             # copy converted ax to dx
    .SET_FIELDS:
        movw    %dx,0(%rdi)                         # temp->tenths_degrees
        and     $1,%cl
        movb    %cl,2(%rdi)                         # temp->is_fahrenheit
    .STFP_FINISH:
        movl    $0,%eax                            
        ret                                         # success
    .ERROR_SENSOR:
        movl    $1,%eax
        ret                                         # no success



#---------------------------------------------------



.data
thou:                           # div contstants
         .int 1000
hund:
         .int 100
tens:
         .int 10
bit_masks:                      # disp bits (val/offset)
        .int 0b1111110          # 0/0 
        .int 0b0001100          # 1/4
        .int 0b0110111          # 2/8
        .int 0b0011111          # 3/12
        .int 0b1001101          # 4/16
        .int 0b1011011          # 5/20
        .int 0b1111011          # 6/24
        .int 0b0001110          # 7/28
        .int 0b1111111          # 8/32
        .int 0b1011111          # 9/36

.text
.global  set_display_from_temp
set_display_from_temp:
    .SDFT_START:
        movw    %di,%r8w                            # r8w holds bytes 0-15 (tenths_degrees)
        andq    $0xFFFF,%r8
        shr     $16,%rdi
        movb    %dil,%cl                            # cl holds bytes 16-23 (is_fahrenheit)
        andq    $0xFF,%rcx
        testb   %cl,%cl                             
        jz      .CELSIUS_CHECK                      # if(!is_fahrenheit)
    .FAHRENHEIT_CHECK:
        cmpb    $1,%cl
        ja      .ERROR_FIELDS                       # if(is_fahrenheit!=0 && is_fahrenheit!=1)                      
        cmpw    $-580,%r8w
        jl      .ERROR_FIELDS                       # (<min fahrenheit)
        cmpw    $1220,%r8w
        jg      .ERROR_FIELDS                       # (>max fahrenheit)
        jmp     .SETUP
    .CELSIUS_CHECK:
        cmpw    $-500,%r8w
        jl      .ERROR_FIELDS                       # (<min celsius)
        cmpw    $500,%r8w
        jg      .ERROR_FIELDS                       # (>max celsius)
    .SETUP:
        pushq   %rbx                                # rbx is a stack temp disp
        pushq   %r12                                # r12 is a stack temp boolean (for possible negative sign)
        movq    $0,%rbx
        movq    $0,%r12
        leaq    bit_masks(%rip),%r11                # r11 points to bit_masks
        movq    $0,%rdi                             # rdi register will be used as a bit_mask bit holder
        cmpw    $-1,%r8w
        jg      .DIGITS                             # tenths_degrees>0
    .CHECK_SIGN:
        movq    $1,%r12                             # neg? true
        movq    $1,%r10
        shl     $14,%r10                            # r10 is neg bit, default to 14th spot (assumes tenths_degrees [-1,-99])
        cmpw    $-100,%r8w
        jg      .NEGATE                             # doesn't need to be shifted to 21st spot (tenths_degrees [-100,-580])
        shl     $7, %r10                           
    .NEGATE:
        neg     %r8w                                # for better division
    .DIGITS:
        cmpw    $100,%r8w
        jb      .TENS_ONES                          # |tenths_degrees| is [0,99]
        cmpw    $1000,%r8w                          
        jb      .HUND                               # |tenths_degrees| is [100,999]
    .THOU:
        movq    $0,%rax                             # clean quotient reg
        movq    $0,%r9                              # clean dividing reg
        movq    $0,%rdx                             # clean remainder reg
        movw    %r8w,%ax
        cwtl
        cltq
        cqto
        movl    thou(%rip),%r9d 
        idivl   %r9d                                # ax holds thou
        movw    %dx,%r8w                            # r8w holds hund,tens,ones
    .SET_THOU:
        cltq
        movl    (%r11,%rax,4),%edi                  
        orl     %edi,%ebx                           
        shl     $7,%ebx                             # bits=(bits|bit_masks[thou])<<7
    .HUND:
        movq    $0,%rdi                             # clean bit reg
        movq    $0,%rax                             # clean quotient reg
        movq    $0,%r9                              # clean dividing reg
        movq    $0,%rdx                             # clean remainder reg
        movw    %r8w,%ax
        cwtl
        cltq
        cqto
        movl    hund(%rip),%r9d
        idivl   %r9d                                # ax holds hund
        movw    %dx,%r8w                            # r8w holds tens,ones
    .SET_HUND:
        cltq
        movl    (%r11,%rax,4),%edi                  
        orl     %edi,%ebx                           
        shl     $7,%ebx                             # bits=(bits|bit_masks[hund])<<7
    .TENS_ONES:
        movq    $0,%rdi                             # clean bit reg
        movq    $0,%rax                             # clean quotient reg
        movq    $0,%r9                              # clean dividing reg
        movq    $0,%rdx                             # clean remainder reg
        movw    %r8w,%ax
        cwtl
        cltq
        cqto
        movl    tens(%rip),%r9d
        idivl   %r9d                                # ax holds tens
        movw    %dx,%r8w                            # r8w holds ones
    .SET_TENS:
        cltq
        movl    (%r11,%rax,4),%edi
        orl     %edi,%ebx                           
        shl     $7,%ebx                             # bits=(bits|bit_masks[tens])<<7
    .SET_ONES:
        movw    %r8w,%ax
        cwtl
        cltq
        movl    (%r11,%rax,4),%edi
        orl     %edi,%ebx                           # bits=(bits|bit_masks[ones])
    .SET_SIGN:
        testq   %r12,%r12
        jz      .SET_STATUS
        orl     %r10d,%ebx                          # turn on neg bit
    .SET_STATUS:
        movq    $1,%r11
        testb   %cl,%cl
        jz      .CELS
    .FAHR:
        shl     $29,%r11
        or      %r11d,%ebx                          # turn on fahr
        jmp     .SDFT_FINISH
    .CELS:
        shl     $28,%r11
        or      %r11d,%ebx                          # turn on cels
    .SDFT_FINISH:
        movl    %ebx,(%rsi)                         # *display=bits
        popq    %r12
        popq    %rbx                                # restoring stack
        movl    $0,%eax
        ret                                         # success
    .ERROR_FIELDS:
        movl $1,%eax
        ret                                         # no success



#---------------------------------------------------



.text
.global thermo_update      
thermo_update:
    .TU_START:
	    movq    $0,%rdx
        pushq   %rdx                                # allocate stack
        leaq    (%rsp),%rdi
        call    set_temp_from_ports                 # (&temp)
        testl   %eax,%eax                           
        jnz     .ERROR_FUNCTIONS                    # ^ returned 1
        movq    (%rdi),%rdi
        leaq    THERMO_DISPLAY_PORT(%rip), %rsi
        call    set_display_from_temp               # (temp,&THERMO_DISPLAY_PORT)
        testl   %eax,%eax
        jnz     .ERROR_FUNCTIONS                    # ^ returned 1
        jmp     .TU_FINISH
    .ERROR_FUNCTIONS:
        popq    %rdx                                # restore stack
        movl    $1,%eax
        ret                                         # no success
    .TU_FINISH:
        popq    %rdx                                # restore stack
        movl    $0,%eax
        ret                                         # success