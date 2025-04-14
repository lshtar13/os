bootSrc="boot.S"
bootObj="boot.o"
kernelSrc="kernel.c"
kernelObj="kernel.o"
linkScript="linker.ld"
binTgt="myos.bin"
rootPath="sysroot"
bootPath="$rootPath/boot"
grubPath="$bootPath/grub"
isoTgt="myos.iso"

echo -n "assemble bootstrap file($bootSrc) ... "
if i686-elf-as $bootSrc -o $bootObj; then
	echo "done!"
else
	echo "failed-exiting"
	exit 1
fi

echo -n "compile kernel source file($kernelSrc) ... "
if i686-elf-gcc -c $kernelSrc -o $kernelObj -std=gnu99 -ffreestanding -O2 -Wall -Wextra; then
	echo "done!"
else
	echo "failed-exiting"
	exit 1
fi

echo -n "link $bootObj and $kernelObj ... "
if i686-elf-gcc -T $linkScript -o $binTgt -ffreestanding -O2 -nostdlib $bootObj $kernelObj -lgcc; then
	echo "done!"
else
	echo "failed-exting"
	exit 1
fi

echo -n "verify multiboot ... "
if grub-file --is-x86-multiboot $binTgt; then
	echo "confirmed!"
else
	echo "failed"
	exit 1
fi

echo -n "create directory $grubPath ... "
if mkdir -p $grubPath; then
	echo "done!"
else
	echo "failed-exiting"
	exit 1
fi

echo -n "copy $binTgt to $bootPath ... "
if cp $binTgt $bootPath/$binTgt; then
	echo "done!"
else
	echo "failed-exiting"
	exit 1
fi

echo -n "copy grub.cfg to $grubPath/grub.cfg ... "
if cp grub.cfg $grubPath/grub.cfg; then
	echo "done!"
else
	echo "failed-exiting"
	exit 1
fi

echo -n "create iso file($isoTgt) from isodir ... "
if grub-mkrescue -o $isoTgt $rootPath; then
	echo "done!"
else
	echo "failed-exiting"
	exit 1
fi

echo "Run 'qemu-system-i386 -cdrom $isoTgt -curses'!"
