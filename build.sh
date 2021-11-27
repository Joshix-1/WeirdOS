#!/usr/bin/sh

NAME="WeirdOS"

# ======== Toolchain
CC="gcc"
CXX="g++"
LD="ld"
EMU="qemu-system-x86_64"
AS="nasm"

# ======== Flags
CXX_FLAGS="-Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -nostdlib"
CC_FLAGS="-Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -nostdlib"

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

	cd src

  # Compile the Bootloader
	echo  "   ==> Compiling ASM Files"
	echo "       > Compiling BOOT.asm"
  $AS Bootloader/BOOT.asm -f bin -o ../build/share/BOOT.bin
  echo "       > Compiling KernelLoader.asm"
  $AS Bootloader/KernelLoader.asm -f elf64 -o ../build/share/KERNEL_LOADER.o
  echo

	# Recursion is Wonderful
	echo	"   ==> Compiling C Files"
	for f in $(find -name '*.c'); do
    echo "       > Compiling $f"
    $CC $CC_FLAGS -o ../build/share/sources/`basename $f`.o -c $f
	done
	echo

	echo	"   ==> Compiling C++ Files"
	for f in $(find -name '*.cpp'); do
    echo "       > Compiling $f"
    $CXX $CXX_FLAGS -o ../build/share/sources/`basename $f`.o -c $f
	done

	echo

	cd ..

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
	$CC -v
	$CXX -v
	$LD -v
	$AS -v
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
