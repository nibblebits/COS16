[BITS 16]
global _disk_reset
global _disk_read_sector
global _disk_get_details
extern _print_number
_disk_reset:
    push bp
    mov bp, sp
    push di
    push si
    mov dl, [bp+4]
    mov ah, 0x00
    int 0x13
    mov ax, 0x01
    jc .error
    jmp .end
.error:
    mov ax, 0x00
.end:
    pop si
    pop di
    pop bp
    ret        

_disk_read_sector:
    push bp
    mov bp, sp
    push di
    push si
    mov ah, 2
    mov al, [bp+14] ; Total sectors
    mov ch, [bp+12] ; Cylinder
    mov cl, [bp+10] ; Sector
    mov dh, [bp+8] ; Head
    mov dl, [bp+6] ; Drive number
    mov bx, [bp+4] ; Destination BX
    int 0x13
    mov ax, 0x01
    jc .error
    jmp .done
.error:
    mov ax, 0x00
.done:
    pop si
    pop di
    pop bp
    ret

_disk_get_details:
    push bp
    mov bp, sp
    push di
    push si
    mov dl, [bp+4]
    mov cx, 0
    mov ah, 0x08
    int 0x13
    jc .error
    
    shr dx, 7
    add dx, 1
    and cl, 0x3f
    mov bx, [bp+6] ; &NumberOfHeads
    mov word [bx], dx
    mov bx, [bp+8] ; &NumberOfSectorsPerTrack
    mov word [bx], cx
    mov ax, 1
    jmp .done
.error:
    mov ax, 0x00
.done:
    mov bx, [bp+6]
    push word [bx]
    ;call _print_number
    pop bx

    pop si
    pop di
    pop bp
    ret