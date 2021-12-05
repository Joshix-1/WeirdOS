#include "Keyboard.h"
#include "../kernel.h"

void BasicKeyboardHandler(unsigned char scancode, unsigned char chr){
    if (chr != 0) {
        kernel.renderer.printChar(chr);
        kernel.renderer.sync();
    }
}

void StartupKeyboardHandler(unsigned char scancode, unsigned char chr){
    switch(chr){
        case 'l':
            kernel.LogRenderer.sync();
            break;
        case 'm':
            kernel.renderer.sync();
    }
}

void Keyboard::KeyboardHandler(unsigned char scancode, unsigned char chr){
    if (!kernel.keyboard.enabled) { return; }
    switch (kernel.keyboard.mode) {
        case 0:
            BasicKeyboardHandler(scancode, chr);
            break;
        case 1:
            StartupKeyboardHandler(scancode, chr);
            break;
    }
}