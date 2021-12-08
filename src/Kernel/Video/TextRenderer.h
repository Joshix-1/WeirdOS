//
// Created by user on 11/26/21.
//

#ifndef WEIRDOS_TEXTRENDERER_H
#define WEIRDOS_TEXTRENDERER_H

#define FRONT_BLACK       0x00
#define FRONT_BLUE        0x01
#define FRONT_GREEN       0x02
#define FRONT_CYAN        0x03
#define FRONT_RED         0x04
#define FRONT_PURPLE      0x05
#define FRONT_BROWN       0x06
#define FRONT_GRAY        0x07
#define FRONT_DARKGRAY    0x08
#define FRONT_LIGHTBLUE   0x09
#define FRONT_LIGHTGREEN  0x0A
#define FRONT_LIGHTCYAN   0x0B
#define FRONT_LIGHTRED    0x0C
#define FRONT_LIGHTPURPLE 0x0D
#define FRONT_YELLOW      0x0E
#define FRONT_WHITE       0x0F

#define BACK_BLACK        0x00
#define BACK_BLUE         0x10
#define BACK_GREEN        0x20
#define BACK_CYAN         0x30
#define BACK_RED          0x40
#define BACK_PURPLE       0x50
#define BACK_BROWN        0x60
#define BACK_GRAY         0x70
#define BACK_BLINK_BLACK  0x80
#define BACK_BLINK_BLUE   0x90
#define BACK_BLINK_GREEN  0xA0
#define BACK_BLINK_CYAN   0xB0
#define BACK_BLINK_RED    0xC0
#define BACK_BLINK_PURPLE 0xD0
#define BACK_BLINK_YELLOW 0xE0
#define BACK_BLINK_WHITE  0xF0

#define STD_COLOR FRONT_WHITE | BACK_BLACK

#define VGA_TEXT_BUFFER (unsigned char *) 0xb8000


class TextRenderer {
    private:
        unsigned char* BUFFER;
        unsigned char color = STD_COLOR;
        int Cursor;

        int X_SIZE = 80;
        int Y_SIZE = 25;
        int BitsPerPixel = 2;

    public:
        const char* name;

        void init(const char* name = "TextRenderer");
        void printChar(char chr, unsigned char color = STD_COLOR);
        void printf(const char* str, ...);
        void ClearScreen(unsigned char bg = 0);
        int GetXPos();
        int GetYPos();
        void sync();
        void scroll();
        void setCursor(unsigned char pos);
};


#endif //WEIRDOS_TEXTRENDERER_H
