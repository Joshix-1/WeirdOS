#include "IDT.h"
#include "KBSets.h"
#include "../IO/IO.h"
#include "../kernel.h"
#include "../Std/log.h"
#include "Keyboard.h"
#include "../Std/Panic.h"

extern IDT64 _idt[256];

/* =============== DESCRIPTORS =============== */

extern unsigned long isr1;
extern unsigned long unknown;

extern unsigned long isr0;
extern unsigned long isr2;
extern unsigned long isr3;
extern unsigned long isr4;
extern unsigned long isr5;
extern unsigned long isr6;
extern unsigned long isr7;
extern unsigned long isr8;
extern unsigned long isr9;
extern unsigned long isr10;
extern unsigned long isr11;
extern unsigned long isr12;
extern unsigned long isr13;
extern unsigned long isr14;
extern unsigned long isr15;
extern unsigned long isr16;
extern unsigned long isr17;
extern unsigned long isr18;
extern unsigned long isr19;
extern unsigned long isr20;
extern unsigned long isr21;
extern unsigned long isr22;
extern unsigned long isr23;
extern unsigned long isr24;
extern unsigned long isr25;
extern unsigned long isr26;
extern unsigned long isr27;
extern unsigned long isr28;
extern unsigned long isr29;
extern unsigned long isr30;
extern unsigned long isr31;

/* =============== ASM FUNCTIONS =============== */
extern "C" void loadIDT();

void SetOffset(IDT64* idt, unsigned long offset){
    idt->offset_low = (unsigned short)((offset & 0x000000000000ffff));
    idt->offset_mid = (unsigned short)((offset & 0x00000000ffff0000) >> 16);
    idt->offset_high = (unsigned int)((offset & 0xffffffff00000000) >> 32);
}
void SetEntry(unsigned char index, unsigned long descriptor, unsigned short sel, unsigned char type){
    _idt[index].zero = 0;
    SetOffset(&_idt[index], descriptor);
    _idt[index].ist = 0;
    _idt[index].selector = sel;
    _idt[index].types_attr = type;
}

void InitializeIDT(){
    for (int i = 0; i < 256; i++){
        SetEntry(i, (unsigned long)&unknown, 0x08, 0x8e);
    }

    InitializeFaults();

    SetEntry(1, (unsigned long)&isr1, 0x08, 0x8e);
//    _idt[1].zero = 0;
//    SetOffset(&_idt[1], (unsigned long)&isr1);
//    _idt[1].ist = 0;
//    _idt[1].selector = 0x08;
//    _idt[1].types_attr = 0x8e;
    IO::RemapPic();

    IO::outb(0x21, 0xfd);
    IO::outb(0xa1, 0xff);
    loadIDT();
}

void InitializeFaults(){
    SetEntry(0, (unsigned long)&isr0, 0x08, 0x8e);
    SetEntry(2, (unsigned long)&isr2, 0x08, 0x8e);
    SetEntry(3, (unsigned long)&isr3, 0x08, 0x8e);
    SetEntry(4, (unsigned long)&isr4, 0x08, 0x8e);
    SetEntry(5, (unsigned long)&isr5, 0x08, 0x8e);
    SetEntry(6, (unsigned long)&isr6, 0x08, 0x8e);
    SetEntry(7, (unsigned long)&isr7, 0x08, 0x8e);
    SetEntry(8, (unsigned long)&isr8, 0x08, 0x8e);
    SetEntry(9, (unsigned long)&isr9, 0x08, 0x8e);
    SetEntry(10, (unsigned long)&isr10, 0x08, 0x8e);
    SetEntry(11, (unsigned long)&isr11, 0x08, 0x8e);
    SetEntry(12, (unsigned long)&isr12, 0x08, 0x8e);
    SetEntry(13, (unsigned long)&isr13, 0x08, 0x8e);
    SetEntry(14, (unsigned long)&isr14, 0x08, 0x8e);
    SetEntry(15, (unsigned long)&isr15, 0x08, 0x8e);
    SetEntry(16, (unsigned long)&isr16, 0x08, 0x8e);
    SetEntry(17, (unsigned long)&isr17, 0x08, 0x8e);
    SetEntry(18, (unsigned long)&isr18, 0x08, 0x8e);
    SetEntry(19, (unsigned long)&isr19, 0x08, 0x8e);
    SetEntry(20, (unsigned long)&isr20, 0x08, 0x8e);
    SetEntry(21, (unsigned long)&isr21, 0x08, 0x8e);
    SetEntry(22, (unsigned long)&isr22, 0x08, 0x8e);
    SetEntry(23, (unsigned long)&isr23, 0x08, 0x8e);
    SetEntry(24, (unsigned long)&isr24, 0x08, 0x8e);
    SetEntry(25, (unsigned long)&isr25, 0x08, 0x8e);
    SetEntry(26, (unsigned long)&isr26, 0x08, 0x8e);
    SetEntry(27, (unsigned long)&isr27, 0x08, 0x8e);
    SetEntry(28, (unsigned long)&isr28, 0x08, 0x8e);
    SetEntry(29, (unsigned long)&isr29, 0x08, 0x8e);
    SetEntry(30, (unsigned long)&isr30, 0x08, 0x8e);
    SetEntry(31, (unsigned long)&isr31, 0x08, 0x8e);
}

/* ===================== HANDLERS ===================== */

extern "C" void isr1_handler(){
    unsigned char scanCode = IO::inb(0x60);
    unsigned char chr = 0;
    if (scanCode < 0x3A){
        chr = KBSetEN::ScanCodeLookupTable[scanCode];
    }
    Keyboard::KeyboardHandler(scanCode, chr);
    IO::outb(0x20, 0x20);
    IO::outb(0xa0, 0x20);
}

extern "C" void unknown_handler(){
    Panic::Throw("Unknown Interrupt detected", 0);
}

/* ========== FAULT's ========== */

extern "C" void isr0_handler(){
    Panic::Throw("CPU Threw Fault: Divide-by-zero Error", 0);
}
extern "C" void isr2_handler(){
    Panic::Throw("CPU Threw Fault: Non-maskable Interrupt", 0);
}
extern "C" void isr3_handler(){
    Panic::Throw("CPU Threw Fault: Breakpoint", 0);
}
extern "C" void isr4_handler(){
    Panic::Throw("CPU Threw Fault: Overflow", 0);
}
extern "C" void isr5_handler(){
    Panic::Throw("CPU Threw Fault: Bound Range Exceeded", 0);
}
extern "C" void isr6_handler(){
    Panic::Throw("CPU Threw Fault: Invalid Opcode", 0);
}
extern "C" void isr7_handler(){
    Panic::Throw("CPU Threw Fault: Device Not Available", 0);
}
extern "C" void isr8_handler(){
    Panic::Throw("CPU Threw Fault: Double Fault", 0);
}
extern "C" void isr9_handler(){
    Panic::Throw("CPU Threw Fault: Coprocessor Segment Overrun", 0);
}
extern "C" void isr10_handler(){
    Panic::Throw("CPU Threw Fault: Invalid TSS", 0);
}
extern "C" void isr11_handler(){
    Panic::Throw("CPU Threw Fault: Segment Not Present", 0);
}
extern "C" void isr12_handler(){
    Panic::Throw("CPU Threw Fault: Stack-Segment Fault", 0);
}
extern "C" void isr13_handler(){
    Panic::Throw("CPU Threw Fault: General Protection Fault", 0);
}
extern "C" void isr14_handler(){
    Panic::Throw("CPU Threw Fault: Page Fault", 0);
}
extern "C" void isr15_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr16_handler(){
    Panic::Throw("CPU Threw Fault: x87 Floating-Point Exception \t", 0);
}
extern "C" void isr17_handler(){
    Panic::Throw("CPU Threw Fault: Alignment Check", 0);
}
extern "C" void isr18_handler(){
    Panic::Throw("CPU Threw Fault: Machine Check", 0);
}
extern "C" void isr19_handler(){
    Panic::Throw("CPU Threw Fault: SIMD Floating-Point Exception", 0);
}
extern "C" void isr20_handler(){
    Panic::Throw("CPU Threw Fault: Virtualization Exception", 0);
}
extern "C" void isr21_handler(){
    Panic::Throw("CPU Threw Fault: Control Protection Exception", 0);
}
extern "C" void isr22_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr23_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr24_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr25_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr26_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr27_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
extern "C" void isr28_handler(){
    Panic::Throw("CPU Threw Fault: Hypervisor Injection Exception", 0);
}
extern "C" void isr29_handler(){
    Panic::Throw("CPU Threw Fault: VMM Communication Exception", 0);
}
extern "C" void isr30_handler(){
    Panic::Throw("CPU Threw Fault: Security Exception", 0);
}
extern "C" void isr31_handler(){
    Panic::Throw("CPU Threw Fault: Reserved", 0);
}
