#include "kernel.h"
#include "Video/TextRenderer.h"
#include "Std/log.h"

// Main Kernel Function
void Kernel::main() {
    log("Kernel > Booted up");
    // Initialize the New TextRenderer to the VGA Output Buffer
    renderer.init((unsigned char *) 0xb8000);
    log("Kernel > TextRenderer Initialized");
    renderer.ClearScreen();

    // Print a Message to make sure the Kernel booted correctly
    renderer.print("[ Kernel - Main ] Booted Up\n");

    return;
}

// Start Function, that's called by the Bootloader
extern "C" void _start(){
    // Start the Kernel
    kernel.main();
}