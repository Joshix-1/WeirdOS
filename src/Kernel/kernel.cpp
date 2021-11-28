#include "kernel.h"
#include "Std/log.h"

// Initialize Basic System
void Kernel::init(){
    // Initialize the New TextRenderer to the VGA Output Buffer
    renderer.init((unsigned char *) 0xb8000);
    renderer.ClearScreen();
    log("Kernel > init > TextRenderer Initialized");
    renderer.print("[ Kernel - Init ] TextRenderer Initialized\n");

    heap.InitializeHeap(0x100000, 0x100000);
    log("Kernel > init > Heap Initialized");
    renderer.print("[ Kernel - Init ] Heap Initialized\n");
}

// Main Kernel Function
void Kernel::main() {
    log("Kernel > main > Booted up");

    init();

    log("Kernel > main > Reached end of Kernel\n");
    renderer.print("[ Kernel - Main ] Reached end of Kernel\n");
    return;
}

// Start Function, that's called by the Bootloader
extern "C" void _start(){
    // Start the Kernel
    kernel.main();
}