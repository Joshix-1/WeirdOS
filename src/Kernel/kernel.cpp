#include "kernel.h"
#include "Std/log.h"
#include "Interrupts/IDT.h"
#include "Interrupts/Keyboard.h"

// Initialize Basic System
void Kernel::init(){
    // Init Basic Memory Management
    heap.InitializeHeap(0x100000, 0x100000);

    LogRenderer.init("Logs");

    // Initialize the New TextRenderer to the VGA Output Buffer
    renderer.init("Stdout");
    renderer.ClearScreen();
    MainRenderer = &renderer;
    logf("Kernel > init > TextRenderer Initialized");

    InitializeIDT();
    logf("Kernel > init > IDT Initialized");
}

// Main Kernel Function
void Kernel::main() {
    init();
    renderer.printf("[ %cKernel%c - %cMain%c ] Init Finished\n", FRONT_CYAN | BACK_BLACK,
                    STD_COLOR, FRONT_GREEN | BACK_BLACK, STD_COLOR);


    // enable Keyboard Input
    keyboard.enabled = true;
    // set mode to StartupKeyboardHandler
    keyboard.mode = 1;
    return;
}

// Start Function, that's called by the Bootloader
extern "C" void _start(){
    // Start the Kernel
    kernel.main();
}