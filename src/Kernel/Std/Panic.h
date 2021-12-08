#ifndef WEIRDOS_PANIC_H
#define WEIRDOS_PANIC_H

namespace Panic {
    void suicide();
    void Throw(const char* exception, unsigned char owner = -1);
}

#endif //WEIRDOS_PANIC_H
