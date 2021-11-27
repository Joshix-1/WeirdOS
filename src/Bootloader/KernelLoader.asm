jmp EnterProtectedMode

%include "Bootloader/Sector2/gdt.asm"
%include "Bootloader/Sector1/print.asm"
%include "Bootloader/Sector2/DetectMemory.asm"

EnterProtectedMode:
    mov bx, Stage2SuccessString
    call Print
    call DetectMemory
    call EnableA20
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp codeseg:StartProtectedMode

EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 32]
%include "Bootloader/Sector2/cpuID.asm"
%include "Bootloader/Sector2/SimplePaging.asm"


StartProtectedMode:

    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call DetectCPUID
    call DetectLongMode
    call SetUpIdentityPaging
    call EditGDT
    jmp codeseg:Start64Bit

[bits 64]
[extern _start]

Start64Bit:
    call ActivateSSE
    call _start
    jmp $

ActivateSSE:
    mov rax, cr0
    and ax, 0b11111101
    or ax, 0b00000001
    mov cr0, rax

    mov rax, cr4
    or ax, 0b1100000000
    mov cr4, rax
    ret


Stage2SuccessString:
    db "[ Bootloader - Stage2] Successfully Started Stage2", 0x0A, 0x0D, 0