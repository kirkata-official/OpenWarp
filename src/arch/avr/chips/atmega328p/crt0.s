.section .text
.global _start
_start:
    ldi r28, 0xFF  ; Initialize Stack Pointer
    ldi r29, 0x08
    out 0x3D, r28
    out 0x3E, r29
    call main      ; Jump to main C code
loop:
    rjmp loop      ; Safety trap