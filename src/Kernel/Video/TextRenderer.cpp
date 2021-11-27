#include "TextRenderer.h"
#include "../IO/IO.h"

void TextRenderer::init(unsigned char *buffer) {
    BUFFER = buffer;
    Cursor = 0;
}

void TextRenderer::printChar(char chr, unsigned char fg, unsigned char bg) {
    switch (chr) {
        case '\n':
            SetCursorPosition(Cursor + X_SIZE - GetXPos());
            break;
        case '\r':
            SetCursorPosition(Cursor - GetXPos());
            break;
        default:
            SetCursorPosition(Cursor + 1);
            *(BUFFER + Cursor * 2) = chr;
            *(BUFFER + Cursor * 2 + 1) = fg | bg;   // Combine Colors to VGA Format
    }
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

void TextRenderer::print(const char *str, unsigned char fg, unsigned char bg) {
    // Iterate through all Chars of the Sting, till it's end ('\0')
    unsigned char* charPtr = (unsigned char*)str;
    while(*charPtr != 0){   // do till end of string reached
        printChar(*charPtr, fg, bg); // Print out the Char
        charPtr++;
    }
}

void TextRenderer::ClearScreen(unsigned char bg) {
    for(unsigned char* i = (unsigned char*)BUFFER; i < BUFFER + 4000; i+=2){
        *i = '\0';
        *(i+1) = bg | 0x0F;
    }
    SetCursorPosition(-1);
}

int TextRenderer::GetXPos(){
    return Cursor % X_SIZE;
}

int TextRenderer::GetYPos(){
    return (int)(Cursor / X_SIZE);
}