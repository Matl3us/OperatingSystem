CC = i686-elf-g++
CFLAGS = -ffreestanding -O2 -Wall -Wextra

SRCS = $(wildcard kernel/*.cpp kernel/**/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: myos.iso

boot.o: kernel/boot.asm
	nasm -f elf32 kernel/boot.asm -o boot.o

gdt_flush.o: kernel/gdt_flush.asm
	nasm -f elf32 kernel/gdt_flush.asm -o gdt_flush.o

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

myos.bin: boot.o gdt_flush.o $(OBJS) 
	$(CC) -T kernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o gdt_flush.o $(OBJS)

myos.iso: myos.bin
	mkdir -p build/boot/grub
	cp myos.bin build/boot/myos.bin
	cp kernel/grub.cfg build/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso build 

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	find . -name "*.o" -delete
	rm -f *.bin *.iso
	rm -rf build 