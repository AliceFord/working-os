disk_load:
    pusha 
    push dx

    mov ah, 0x02 ; read
    mov al, dh ; num sectors
    mov cl, 0x02 ; start sector 2
    mov ch, 0x00 ; cylinder 0
    mov dh, 0x00 ; head 0

    int 0x13 ; BIOS interrupt
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:
    jmp disk_loop

sectors_error:
    jmp disk_loop

disk_loop:
    jmp $
