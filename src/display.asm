[BITS 16]
global _putchar

_putchar:
    push bp
    mov bp, sp
    push di
    push si
    mov al, [bp+4]
    mov ah, 0eh
    int 0x10
    pop si
    pop di
    pop bp
    ret        

