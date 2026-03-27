CC = i686-elf-g++
CFLAGS = -ffreestanding -O1 -Wall -Wextra

SRCS_CPP = $(wildcard kernel/*.cpp kernel/**/*.cpp)
OBJS_CPP = $(SRCS_CPP:.cpp=.o)

SRCS_ASM = $(wildcard kernel/*.asm kernel/**/*.asm)
OBJS_ASM = $(SRCS_ASM:.asm=.asm.o)

all: myos.iso

%.asm.o: %.asm
	nasm -f elf32 $< -o $@

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

myos.bin: $(OBJS_ASM) $(OBJS_CPP) 
	$(CC) -T kernel/linker.ld -o myos.bin -ffreestanding -O1 -nostdlib $(OBJS_ASM) $(OBJS_CPP)

myos.iso: myos.bin
	mkdir -p build/boot/grub
	cp myos.bin build/boot/myos.bin
	cp kernel/grub.cfg build/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso build 

run: myos.iso
	qemu-system-i386 -cdrom myos.iso -serial stdio

clean:
	find . -name "*.o" -delete
	rm -f *.bin *.iso
	rm -rf build 