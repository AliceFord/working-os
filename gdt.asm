gdt_start:
    dq 0x0

gdt_code:
    dw 0xffff ; segment length
    dw 0x0 ; segment base
    db 0x0 ; segment base
    db 10011010b ; flags 
    db 11001111b ; flags
    db 0x0 ; segment base

gdt_data:
    dw 0xffff ; segment length
    dw 0x0 ; segment base
    db 0x0 ; segment base
    db 10010010b ; flags 
    db 11001111b ; flags
    db 0x0 ; segment base

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt2_start:
    dq 0x0

gdt2_code:
    dw 0xffff ; segment length
    dw 0x0 ; segment base
    db 0x0 ; segment base
    db 10011010b ; flags 
    db 11001111b ; flags
    db 0x0 ; segment base

gdt2_data:
    dw 0xffff ; segment length
    dw 0x0 ; segment base
    db 0x0 ; segment base
    db 10010010b ; flags 
    db 11001111b ; flags
    db 0x0 ; segment base

gdt2_end:

gdt2_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
CODE_SEG2 equ gdt2_code - gdt2_start
DATA_SEG2 equ gdt2_data - gdt2_start
