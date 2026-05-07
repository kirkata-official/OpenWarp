    .section .vectors, "ax"
    .align   4

    .literal_position

    .global _start
    .type   _start, @function
_start:
    rsil    a2, 15              

    movi    a1, _stack_top
    addi    a1, a1, -16        

    movi    a0, 0
    s32i    a0, a1, 0
    s32i    a0, a1, 4
    s32i    a0, a1, 8
    s32i    a0, a1, 12

    movi    a2, _bss_start
    movi    a3, _bss_end
    movi    a4, 0
.bss_loop:
    bge     a2, a3, .bss_done
    s32i    a4, a2, 0
    addi    a2, a2, 4
    j       .bss_loop
.bss_done:
    rsil    a2, 0
    call8   main

.hang:
    j       .hang

    .size   _start, . - _start

    .org    0x100               
    .global _double_exception_vector
_double_exception_vector:
    j       _double_exception_vector

    .section .text, "ax"
    .align  4
    .global _level1_vector
_level1_vector:
    j       _level1_vector
