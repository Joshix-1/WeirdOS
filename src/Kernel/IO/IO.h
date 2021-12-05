#ifndef WEIRDOS_IO_H
#define WEIRDOS_IO_H

#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1

#define ICW1_INIT       0x10
#define ICW1_ICW4       0x01
#define ICW4_8086       0x01

// Some Basic Input Output Functions
namespace IO {
    void outb(unsigned short port, unsigned char val);
    unsigned char inb(unsigned short port);
    void RemapPic();
}
#endif //WEIRDOS_IO_H
