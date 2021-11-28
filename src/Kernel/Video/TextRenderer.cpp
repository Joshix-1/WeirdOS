#include "TextRenderer.h"
#include "../IO/IO.h"
#include "../kernel.h"
#include "../Memory/Memory.h"

void TextRenderer::init() {
    BUFFER = (unsigned char*)kernel.heap.malloc(4000);
    Cursor = 0;
}

void TextRenderer::printChar(char chr, unsigned char fg, unsigned char bg) {
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
            *(BUFFER + Cursor * 2 + 1) = fg | bg;   // Combine Colors to VGA Format
            Cursor++;
    }
}

void TextRenderer::print(const char *str, unsigned char fg, unsigned char bg) {
    // Iterate through all Chars of the Sting, till it's end ('\0')
    unsigned char* charPtr = (unsigned char*)str;
    while(*charPtr != 0){   // do till end of string reached
        printChar(*charPtr, fg, bg); // Print out the Char
        charPtr++;
    }
    sync();
}

void TextRenderer::ClearScreen(unsigned char bg) {
    for(unsigned char* i = (unsigned char*)BUFFER; i < BUFFER + 4000; i+=2){
        *i = '\0';
        *(i+1) = bg | 0x0F;
    }
    Cursor = 0;
    sync();
}

int TextRenderer::GetXPos(){
    return Cursor % X_SIZE;
}

int TextRenderer::GetYPos(){
    return (int)(Cursor / X_SIZE);
}

void TextRenderer::sync() {
    // Swap the Buffer to VGA output
    memcpy(VGA_TEXT_BUFFER, BUFFER, 4000);
    // Do some weird magic to tell the Computer to move the Cursor to the position
    IO::outb(0x3D4, 0x0F);
    IO::outb(0x3D5, (unsigned char)(Cursor & 0xFF));
    IO::outb(0x3D4, 0x0E);
    IO::outb(0x3D5, (unsigned char)(Cursor >> 8) & 0xFF);
}