//
// Created by user on 11/27/21.
//

#include "log.h"
#include "../IO/IO.h"
#include "../Std/Convert.h"
#include "../Video/TextRenderer.h"
#include "../kernel.h"
#include <cstdarg>

void logString(const char* str){
    unsigned char* charPtr = (unsigned char*)str;
    while(*charPtr != 0){   // do till end of string reached
        IO::outb(0x3F8, *charPtr); // Print out the Char
        kernel.LogRenderer.printChar(*charPtr);
        charPtr++;
    }
}

void logf(const char* str, ...) {
    va_list valist;
    unsigned char* charPtr = (unsigned char*)str;

    va_start(valist, str);
    while(*charPtr != 0){   // do till end of string reached
        if (*charPtr == '%') {
            char code = *(charPtr + 1);
            switch (code) {
                case 'i':
                    logString(Convert::IntegerToString(va_arg(valist, int)));
                    break;
                case 'f':
                    logString(Convert::FloatToString(va_arg(valist, double), 2));
            }
            charPtr++;
        }else {
            IO::outb(0x3F8, *charPtr); // Print out the Char
            kernel.LogRenderer.printChar(*charPtr);
        }
        charPtr++;
    }
    va_end(valist);

    IO::outb(0x3F8, '\n');
    kernel.LogRenderer.printChar('\n');
    kernel.LogRenderer.sync();
}