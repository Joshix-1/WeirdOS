[org 0x7c00]

mov bx, WelcomeMsg
call Print

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

call ReadDisk

jmp PROGRAM_SPACE

%include "Sector1/print.asm"
%include "Sector1/diskread.asm"

WelcomeMsg:
    db "!===== WeirdOS - Bootloader =====!", 0x0A, 0x0D, 0

times 510 - ($ - $$) db 0

dw 0xaa55