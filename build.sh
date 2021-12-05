#!/usr/bin/sh

NAME="WeirdOS"

# ======== Toolchain
CC="gcc"
CXX="g++"
LD="ld"
EMU="qemu-system-x86_64"
AS="nasm"

echo	"#########################################"
echo	"##   Welcome to WeirdOS build Script   ##"
echo	"#########################################"
echo	""


set -e  # Stop the Script when errors occur

build(){
	echo	"!===== Building WeirdOS"

  # Cleaning up Objects Folder
  rm -r build/share
  mkdir build/share
  mkdir build/share/sources

	cd src/Bootloader

  # Compile the Bootloader
	echo  "   ==> Compiling Bootloader"
	echo "       > Compiling BOOT.asm"
  $AS BOOT.asm -f bin -o ../../build/share/BOOT.bin
  echo "       > Compiling KernelLoader.asm"
  $AS KernelLoader.asm -f elf64 -o ../../build/share/KERNEL_LOADER.o
  echo

  cd ../Kernel
	# Recursion is Wonderful
	echo	"   ==> Compiling ASM Files"
	for f in $(find -name '*.asm'); do
    echo "       > Compiling $f"
    $AS $f -f elf64 -o ../../build/share/sources/`basename $f`.o
	done
	echo

	echo	"   ==> Compiling C Files"
	for f in $(find -name '*.c'); do
    echo "       > Compiling $f"
    $CC -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -nostdlib -o ../../build/share/sources/`basename $f`.o -c $f
	done
	echo

	echo	"   ==> Compiling C++ Files"
	for f in $(find -name '*.cpp'); do
    echo "       > Compiling $f"
    $CXX -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -nostdlib -o ../../build/share/sources/`basename $f`.o -c $f
	done

	echo

	cd ../..

  # Create an Archive (KERNEL.a) with all the Object Files in it
	echo  "   ==> Combining Object Files"
	cd build/share/sources
	for dir in *.o; do
	  ar rc ../KERNEL.a $dir
	done
	cd ../../..

  echo
}

buildimg(){
	echo 	"!===== Building ISO Image"
	# Link Kernel and Second Stage Bootloader togehter
	echo  "   ==> Linking Files"
	cd build
	$LD -T "config/WeirdOS.ld" -static -nostdlib

  # Put First Stage Bootloader and the Linked Stuff in one File
	echo "   ==> 'WEIRD_OS.bin'"
  cat share/BOOT.bin share/KERNEL.bin > share/WEIRD_OS.bin

  # Clear ISO Image root Folder
  rm -r iso/boot
  mkdir iso/boot

  # Create ISO Image
  echo "   ==> Generating ISO image"
  cp share/WEIRD_OS.bin iso/boot/weirdos.bin
  truncate iso/boot/weirdos.bin -s 1200k
  mkisofs -b boot/weirdos.bin -o $NAME.iso iso/

  cd ..
}

run(){
	echo 	"!===== Running '$NAME'"
	$EMU -cdrom build/$NAME.iso -machine q35 -m 256M -cpu qemu64 -serial file:serial.log
}

check(){
	echo	"!===== Starting System checks"
	if ! [ -x "$(command -v $CC)" ]; then
    echo "Error: $CC is not installed." >&2
    exit 1
  fi
  if ! [ -x "$(command -v $CXX)" ]; then
    echo "Error: $CXX is not installed." >&2
    exit 1
  fi
  if ! [ -x "$(command -v $LD)" ]; then
    echo "Error: $LD is not installed." >&2
    exit 1
  fi
	if ! [ -x "$(command -v $AS)" ]; then
    echo "Error: $AS is not installed." >&2
    exit 1
  fi
  if ! [ -x "$(command -v mkisofs)" ]; then
    echo "Error: mkisofs is not installed." >&2
    exit 1
  fi
	echo "\n!===== System Checks -> OK"
}


case $1 in
	check)
		check
		exit
		;;

	build)
		build
		buildimg
		exit
		;;

	run)
		run
		exit
		;;

  build_run)
    build
    buildimg
    run
    exit;
esac


echo "Unknown MODE '$1' - Starting Standard Build and Run"
check
build
buildimg
run

