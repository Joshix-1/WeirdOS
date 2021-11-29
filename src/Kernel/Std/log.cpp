//
// Created by user on 11/27/21.
//

#include "log.h"
#include "../IO/IO.h"
#include "../Std/Convert.h"
#include <cstdarg>

void logf(const char* str, ...) {
    va_list valist;
    unsigned char* charPtr = (unsigned char*)str;

    va_start(valist, str);
    while(*charPtr != 0){   // do till end of string reached
        if (*charPtr == '%') {
            char code = *(charPtr + 1);
            switch (code) {
                case 'i':
                    logf(Convert::IntegerToString(va_arg(valist, int)));
                    break;
                case 'f':
                    logf(Convert::FloatToString(va_arg(valist, double), 2));
            }
            charPtr++;
        }else {
            IO::outb(0x3F8, *charPtr); // Print out the Char
        }
        charPtr++;
    }
    va_end(valist);

    IO::outb(0x3F8, '\n');
}