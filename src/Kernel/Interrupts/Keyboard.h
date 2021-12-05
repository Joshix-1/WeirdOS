#ifndef WEIRDOS_KEYBOARD_H
#define WEIRDOS_KEYBOARD_H

namespace Keyboard {
    struct KeyboardData {
        bool enabled;
        bool shift;

        unsigned char mode;
        // ##############################
        // ########### MODES ############
        // ## 0 - Basic                ##
        //###############################
    };

    void KeyboardHandler(unsigned char scancode, unsigned char chr);
}
#endif //WEIRDOS_KEYBOARD_H
