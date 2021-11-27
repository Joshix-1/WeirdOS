//
// Created by user on 11/27/21.
//

#include "log.h"
#include "../IO/IO.h"

void log(const char* str) {
    unsigned char* charPtr = (unsigned char*) str;
    while (*charPtr != 0) {
        IO::outb(0x3F8, *charPtr);
        charPtr++;
    }
    IO::outb(0x3F8, '\n');
}