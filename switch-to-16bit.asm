[global Entry16]
[bits 32]

%include "gdt2.asm"

idt_real:
	dw 0x3ff		; 256 entries, 4b each = 1K
	dd 0			; Real Mode IVT @ 0x0000
 
savcr0:
	dd 0			; Storage location for pmode CR0.

Entry16:
        ; We are already in 16-bit mode here!
 
	cli			; Disable interrupts.
 
	; Need 16-bit Protected Mode GDT entries!
	mov eax, DATA_SEG2	; 16-bit Protected Mode data selector.
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax

	; Disable paging (we need everything to be 1:1 mapped).
	mov eax, cr0
	mov [savcr0], eax	; save pmode CR0
	and eax, 0x7ffffffe	; Disable paging bit & disable 16-bit pmode.
    jmp stage2

[bits 16]
stage2:
    mov cr0, eax

	jmp 0:GoRMode		; Perform Far jump to set CS.

[bits 16]
GoRMode:
	mov sp, 0x8000		; pick a stack pointer.
	mov ax, 0		; Reset segment registers to 0.
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	lidt [idt_real]
	sti			; Restore interrupts -- be careful, unhandled int's will kill it.
    
    mov ah, 0x0e 
    mov bh, 0  
    mov bl, 4  
    mov cx, 1  
    mov al, 48
    int 0x10
    
    jmp $
