#ifndef WEIRDOS_IO_H
#define WEIRDOS_IO_H

// Some Basic Input Output Functions
namespace IO {
    void outb(unsigned short port, unsigned char val);
    unsigned char inb(unsigned short port);
}
#endif //WEIRDOS_IO_H
