#include "kernel.h"
#include "Std/log.h"

// Initialize Basic System
void Kernel::init(){
    // Init Basic Memory Management
    heap.InitializeHeap(0x100000, 0x100000);
    log("Kernel > init > Heap Initialized");

    // Initialize the New TextRenderer to the VGA Output Buffer
    renderer.init();
    renderer.ClearScreen();
    log("Kernel > init > TextRenderer Initialized");
}

// Main Kernel Function
void Kernel::main() {
    log("Kernel > main > Booted up");

    init();
    renderer.printf("[ %cKernel%c - %cMain%c ] Init Finished\n", FRONT_CYAN | BACK_BLACK, STD_COLOR, FRONT_GREEN | BACK_BLACK, STD_COLOR);

    log("Kernel > main > Reached end of Kernel\n");
    renderer.printf("[ %cKernel%c - %cMain%c ] %cWARNING:%c Reached end of Kernel\n", FRONT_CYAN | BACK_BLACK, STD_COLOR, FRONT_GREEN | BACK_BLACK, STD_COLOR, FRONT_RED | BACK_BLACK, STD_COLOR);
    return;
}

// Start Function, that's called by the Bootloader
extern "C" void _start(){
    // Start the Kernel
    kernel.main();
}