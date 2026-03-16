CC = i686-elf-g++
CFLAGS = -ffreestanding -O2 -Wall -Wextra

all: myos.iso

boot.o: kernel/boot.asm
	nasm -f elf32 kernel/boot.asm -o boot.o

kernel.o: kernel/kernel.cpp
	$(CC) $(CFLAGS) -c kernel/kernel.cpp -o kernel.o

myos.bin: boot.o kernel.o
	$(CC) -T kernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o

myos.iso: myos.bin
	mkdir -p build/boot/grub
	cp myos.bin build/boot/myos.bin
	cp kernel/grub.cfg build/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso build 

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f *.o *.bin *.iso
	rm -rf build 