#include "TextRenderer.h"
#include "../IO/IO.h"

void TextRenderer::init(unsigned char *buffer) {
    BUFFER = buffer;
    Cursor = 0;
}

void TextRenderer::printChar(char c, unsigned char color) {
    *(BUFFER + Cursor * 2) = c;
    *(BUFFER + Cursor * 2 + 1) = color;
    SetCursorPosition(Cursor + 1);
}

void TextRenderer::SetCursorPosition(int position) {
    // Do some weird magic to tell the Computer to move the Cursor to the position
    IO::outb(0x3D4, 0x0F);
    IO::outb(0x3D5, (unsigned char)(position & 0xFF));
    IO::outb(0x3D4, 0x0E);
    IO::outb(0x3D5, (unsigned char)(position >> 8) & 0xFF);

    // Update Cursor Variable
    Cursor = position;
}

void TextRenderer::print(const char *str, unsigned char color) {
    // Iterate through all Chars of the Sting, till it's end ('\0')
    unsigned char* charPtr = (unsigned char*)str;
    while(*charPtr != 0){   // do till end of string reached
        printChar(*charPtr, color); // Print out the Char
        charPtr++;
    }
}

void TextRenderer::ClearScreen(long long ClearColor) {
    long long value = 0;
    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;
    for(long long* i = (long long*)BUFFER; i < (long long*)(BUFFER + 4096); i++){
        *i = value;
    }
}