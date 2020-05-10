ORG 0x7c00
[BITS 16]

jmp short start
nop

; FAT16 header  
OEMIdentifier   db 'COS16   '
BytesPerSector 		dw 0x200	; 512 bytes per sector
SectorsPerCluster	db 0x80		;
ReservedSectors 	dw 0x02		; Reserved sectors before FAT (TODO: is this BOOT?)
FATCopies		db 0x02		  ; Often this value is 2.
RootDirEntries 		dw 0x0800	; Root directory entries
NumSectors		dw 0x0000	;  If this value is 0, it means there are more than 65535 sectors in the volume
MediaType		db 0xF8		; Fixed disk -> Harddisk
SectorsPerFAT		dw 0x0100	; Sectors used by each FAT Table
SectorsPerTrack		dw 0x20		; TODO: Look up? BIOS might change those
NumberOfHeads		dw 0x40		; Does this even matter?
HiddenSectors		dd 0x00
SectorsBig		dd 0x773594		;

; Extended BPB (DOS 4.0)
DriveNumber		db 0x80		; 0 for removable, 0x80 for hard-drive
WinNTBit		db 0x00		; WinNT uses this
Signature		db 0x29		; DOS 4.0 EBPB signature
VolumeID		dd 0x0000D105	; Volume ID
VolumeIDString		db "COS16 BOOT "; Volume ID
SystemIDString		db "FAT16   "   ; File system type, pad with blanks to 8 bytes


start:

; RESET THE DISK
; DL Register contains current drive as passed to us by bios
; Won't bother checking status here waste of time its emulated
mov ah, 0x00
int 0x13

; Segment where kernel will load
mov ax, 0x7e0
mov es, ax

; LOAD KERNEL INTO MEMORY
kernel_load:
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x00
    int 0x13
    jc .problem

    mov ax, 0x7e0
    mov ds, ax

    ; Jump to the loaded kernel
    jmp 0x7e0:00
.problem:
    mov si, problem_loading_kernel
    call print
    jmp $

print:
    push ax
    mov ah, 0eh
.nextc:
    lodsb
    cmp al, 0
    je .pdone
    int 0x10
    jmp .nextc
.pdone:
    pop ax
    ret


problem_loading_kernel: db 'Issue loading the kernel ensure medium is large enough and contains valid kernel', 0

TIMES 510-($-$$) db 0
dw 0xAA55
