[BITS 16]
global _putchar

_putchar:
    push bp
    mov bp, sp
    mov al, [bp+4]
    mov ah, 0eh
    int 0x10
    pop bp
    ret        

