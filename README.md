# WeirdOS

WeirdOS is a basic x86_64 Operating System written in C++

WeidOS is also a try to make a friend an OSdev.

## Building Dependencies
* gcc (and g++)
* ld
* qemu-system-x86_64
* nasm
* mkisofs
* Linux Kernel based OS

## Build
### Standard
To build WeirdOS, just run:
```shell
bash build.sh
```
This will:
* Check the Build Dependencies
* Build the Source Files
* Build the Image
* Run the Image in QEMU

### Other Build Options are:
* check     -> Check the Dependencies
* build     -> Build Sources and Image
* run       -> Run the Image
* build_run -> Build and Run
