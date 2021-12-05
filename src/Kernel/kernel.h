//
// Created by user on 11/27/21.
//

#ifndef WEIRDOS_KERNEL_H
#define WEIRDOS_KERNEL_H

#include "Video/TextRenderer.h"
#include "Memory/Heap.h"
#include "Interrupts/Keyboard.h"

#define kernel Kernel::Instance()

class Kernel{
public:
    TextRenderer renderer;
    TextRenderer LogRenderer;
    TextRenderer* MainRenderer;
    Heap heap;
    Keyboard::KeyboardData keyboard;

    void main();
    void init();

    static Kernel& Instance() {
        static Kernel singleton;
        return singleton;
    }
};

#endif //WEIRDOS_KERNEL_H
