[bits 16]
[org 0x7c00]
; Where to load kernel
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

; setup stack
mov bp, 0x9000
mov sp, bp

call load_kernel

call switch_to_32bit

jmp $ ; loop forever

%include "disk.asm"
%include "gdt.asm"
%include "switch-to-32bit.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; destination
    mov dh, 32 ; num sectors
    mov dl, [BOOT_DRIVE] ; disk
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
    call KERNEL_OFFSET ; hand control to kernel
    jmp $ ; loop forever

BOOT_DRIVE db 0

times 510 - ($-$$) db 0
dw 0xaa55
