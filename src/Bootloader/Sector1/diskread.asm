PROGRAM_SPACE equ 0x8000

ReadDisk:
    mov ah, 0x02
    mov bx, PROGRAM_SPACE
    mov al, 64
    mov dl, [BOOT_DISK]
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13

    jc DiskReadFailed

    call DiskReadSuccess
    ret

BOOT_DISK:
    db 0

DiskReadErrorString:
    db "[ Bootloader - Stage1] Failed to read from the Disk!", 0x0A, 0x0D, 0

DiskReadSuccessString:
    db "[ Bootloader - Stage1] Successfully reading from the Disk!", 0x0A, 0x0D, 0

DiskReadFailed:
    mov bx, DiskReadErrorString
    call Print

DiskReadSuccess:
    mov bx, DiskReadSuccessString
    call Print
