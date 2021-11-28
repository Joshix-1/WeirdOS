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

    log("Kernel > main > Reached end of Kernel\n");
    renderer.print("[ Kernel - Main ] Reached end of Kernel\n");
    return;
}

// Start Function, that's called by the Bootloader
extern "C" void _start(){
    // Start the Kernel
    kernel.main();
}