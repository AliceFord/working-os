[global Entry16]
[bits 16]

%include "gdt2.asm"

idt_real:
	dw 0x3ff
	dd 0		
 
savcr0:
	dd 0

Entry16:
 
	cli			
 
	mov eax, DATA_SEG2	
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax

	;int 0x01
	mov eax, cr0
	
	mov [savcr0], eax
	and eax, 0x7ffffffe	

    mov cr0, eax

	jmp 0:GoRMode		; Far jump

[bits 16]
GoRMode:
	mov sp, 0x8000		; pick a stack pointer.
	mov ax, 0	
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	lidt [idt_real]
	sti	
    
    jmp $
