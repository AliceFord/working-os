[bits 16]
[org 0x7c00]
; Where to load kernel
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

; setup stack
mov bp, 0x9000
mov sp, bp

; Set VGA mode

; mov ah, 0x4f
; mov al, 0x02
; mov bh, 0x115 ; 0x13 -> 40 x 25
; int 0x10

mov ax, 0x4f02
mov bx, 0x4112
int 0x10

; 80 x 30 text mode essentially
call load_kernel

call switch_to_32bit

jmp $ ; loop forever

%include "disk.asm"
%include "gdt.asm"
%include "switch-to-32bit.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; destination
    mov dh, 48 ; num sectors
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
