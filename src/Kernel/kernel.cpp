#include "Video/TextRenderer.h"

// Main Kernel Function
int main() {
    TextRenderer renderer;
    // Initialize the New TextRenderer to the VGA Output Buffer
    renderer.init((unsigned char *) 0xb8000);
    renderer.ClearScreen();

    // Print a Message to make sure the Kernel booted correctly
    renderer.print("[ Kernel - Main ] Started Kernel");

    return 0;
}

// Start Function, that's called by the Bootloader
extern "C" void _start(){
    // Start the Kernel
    main();

    return;
}