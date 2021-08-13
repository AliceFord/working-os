gdt2_start:
    dq 0x0

gdt2_code:
    dw 0xffff ; segment length
    dw 0x0 ; segment base
    db 0x0 ; segment base
    db 10011010b ; flags 
    db 00001111b ; flags
    db 0x0 ; segment base

gdt2_data:
    dw 0xffff ; segment length
    dw 0x0 ; segment base
    db 0x0 ; segment base
    db 10010010b ; flags 
    db 00001111b ; flags
    db 0x0 ; segment base

gdt2_end:

gdt2_descriptor:
    dw gdt2_end - gdt2_start
    dd gdt2_start

CODE_SEG2 equ gdt2_code - gdt2_start
DATA_SEG2 equ gdt2_data - gdt2_start
