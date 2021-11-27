//
// Created by user on 11/27/21.
//

#ifndef WEIRDOS_KERNEL_H
#define WEIRDOS_KERNEL_H

#define kernel Kernel::Instance()

class Kernel{
public:
    TextRenderer renderer;

    void main();
    static Kernel& Instance() {
        static Kernel singleton;
        return singleton;
    }
};

#endif //WEIRDOS_KERNEL_H
