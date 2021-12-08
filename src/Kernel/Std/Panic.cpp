#include "Panic.h"
#include "../Video/TextRenderer.h"
#include "../kernel.h"
#include "log.h"

void Panic::suicide() {
    logf("Panic > suicide > Klick");
    logf("Panic > suicide > Peng");

    while (true){
        asm volatile ("hlt");
    }
}

void Panic::Throw(const char *exception, unsigned char owner) {
    kernel.renderer.printf("%c!===== KERNEL PANIC =====!\n", BACK_BLACK | FRONT_RED);

    TextRenderer renderer;
    renderer.init("KERNEL_PANIC");
    renderer.ClearScreen(BACK_RED);

    renderer.printf("%c!===== KERNEL PANIC =====!\n", BACK_RED | FRONT_WHITE);
    renderer.printf("Owner with ID '%i' caused a Kernel Panic.\n\n", owner);
    renderer.printf("EXCEPTION: \n");
    renderer.printf(exception);

    logf("!===== KERNEL PANIC =====!");
    logf("Owner with ID '%i' caused a Kernel Panic.\n", owner);
    logf("EXCEPTION: ");
    logf(exception);

    kernel.MainRenderer = &renderer;
    renderer.sync();

    // and bye
    suicide();
}