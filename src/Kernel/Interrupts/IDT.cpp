#include "IDT.h"
#include "KBSets.h"
#include "../IO/IO.h"
#include "../kernel.h"
#include "../Std/log.h"
#include "Keyboard.h"

extern IDT64 _idt[256];
extern unsigned long isr1;

// Assembly Functions
extern "C" void loadIDT();

void SetOffset(IDT64* idt, unsigned long offset){
    idt->offset_low = (unsigned short)((offset & 0x000000000000ffff));
    idt->offset_mid = (unsigned short)((offset & 0x00000000ffff0000) >> 16);
    idt->offset_high = (unsigned int)((offset & 0xffffffff00000000) >> 32);
}

void InitializeIDT(){
//    for (int i = 0; i < 256; i++){
//        _idt[i].zero = 0;
//        SetOffset(&_idt[i], (uint64_t)&UnknownFault);
//        _idt[i].ist = 0;
//        _idt[i].selector = 0x08;
//        _idt[i].types_attr = 0x8e;
//    }

    _idt[1].zero = 0;
    SetOffset(&_idt[1], (unsigned long)&isr1);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;
    _idt[1].types_attr = 0x8e;
    IO::RemapPic();

    IO::outb(0x21, 0xfd);
    IO::outb(0xa1, 0xff);
    loadIDT();
}

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