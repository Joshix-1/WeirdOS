#include "TextRenderer.h"
#include "../IO/IO.h"
#include "../kernel.h"
#include "../Memory/Memory.h"
#include "../Std/log.h"
#include "../Std/Convert.h"
#include <cstdarg>

void TextRenderer::init(const char* _name) {
    name = _name;
    BUFFER = (unsigned char*)kernel.heap.malloc((X_SIZE * Y_SIZE * BitsPerPixel));
    Cursor = 0;
}

void TextRenderer::printChar(char chr, unsigned char color) {
    // SYNC AFTER CALLING THIS FUNCTION!!!
    switch (chr) {
        case '\n':
            Cursor += X_SIZE - GetXPos();
            break;
        case '\r':
            Cursor -= GetXPos();
            break;
        default:
            *(BUFFER + Cursor * 2) = chr;
            *(BUFFER + Cursor * 2 + 1) = color;   // Combine Colors to VGA Format
            Cursor++;
    }
    if (Cursor >= (X_SIZE * Y_SIZE)){
        scroll();
    }
}

void TextRenderer::printf(const char* str, ...) {
    /*
     * Formatting Codes:
     * c - set Color till next %c
     * i - print Integer
     * f - print Float
     * */
    va_list valist;
    unsigned char* charPtr = (unsigned char*)str;

    va_start(valist, str);
    while(*charPtr != 0){   // do till end of string reached
        if (*charPtr == '%') {
            char code = *(charPtr + 1);
            switch (code) {
                case 'c':
                    color = va_arg(valist, int);
                    break;
                case 'i':
                    printf(Convert::IntegerToString(va_arg(valist, int)));
                    break;
                case 'f':
                    printf(Convert::FloatToString(va_arg(valist, double), 2));
            }
            charPtr++;
        }else {
            printChar(*charPtr, color); // Print out the Char
        }
        charPtr++;
    }
    va_end(valist);
    sync();
}

void TextRenderer::ClearScreen(unsigned char bg) {
    for(unsigned char* i = (unsigned char*)BUFFER; i < BUFFER + (X_SIZE * Y_SIZE * BitsPerPixel); i+=2){
        *i = '\0';
        *(i+1) = bg | 0x0F;
    }
    sync();
}

int TextRenderer::GetXPos(){
    return Cursor % X_SIZE;
}

int TextRenderer::GetYPos(){
    return (int)(Cursor / X_SIZE);
}

void TextRenderer::sync() {
    if (kernel.MainRenderer == this) {
        // Swap the Buffer to VGA output
        memcpy(VGA_TEXT_BUFFER, BUFFER, (X_SIZE * Y_SIZE * BitsPerPixel));
        // Do some weird magic to tell the Computer to move the Cursor to the position
        IO::outb(0x3D4, 0x0F);
        IO::outb(0x3D5, (unsigned char)(Cursor & 0xFF));
        IO::outb(0x3D4, 0x0E);
        IO::outb(0x3D5, (unsigned char)(Cursor >> 8) & 0xFF);
    }
}

void TextRenderer::scroll(){
    void* Clipboard = kernel.heap.malloc((X_SIZE * (Y_SIZE-1) * BitsPerPixel));
    memcpy(Clipboard, (BUFFER+X_SIZE * BitsPerPixel), (X_SIZE * (Y_SIZE-1) * BitsPerPixel));
    ClearScreen();
    memcpy(BUFFER, Clipboard, (X_SIZE * (Y_SIZE-1) * BitsPerPixel));
    kernel.heap.free(Clipboard);
    Cursor -= X_SIZE;
    sync();
    return;
}

void TextRenderer::setCursor(unsigned char pos) {
    Cursor = pos;
    sync();
}