# Operating System
 
A minimal x86 operating system kernel built from scratch in C++ and x86 assembly, bootable via GRUB.
 
## Features
 
- **Bootloader**: Multiboot-compliant, loaded by GRUB
- **GDT**: Global Descriptor Table with kernel code and data segments
- **IDT / ISR / IRQ**: Interrupt handling for CPU exceptions and hardware interrupts
- **PIC**: 8259 Programmable Interrupt Controller with remapped IRQ vectors
- **PIT**: Programmable Interval Timer running at 100 Hz
- **PMM**: Physical Memory Manager using a bitmap allocator
- **Paging**: Basic identity-mapped page directory (4 MB)
- **Heap**: Simple bump allocator (`kmalloc` / `kfree`)
- **Keyboard**: PS/2 keyboard driver via scancode table
- **VGA Terminal**: 80×25 text-mode terminal with cursor support
- **Serial**: COM1 debug output
- **Shell**: Minimal command-line shell with `help`, `clear`, `meminfo`, and `time`
 
## Requirements
 
- `i686-elf-g++` cross-compiler
- `nasm`
- `grub-mkrescue` and `xorriso`
- `qemu-system-i386` (for running)
 
## Building & Running
 
```bash
# Build the ISO
make
 
# Run in QEMU
make run
 
# Clean build artifacts
make clean
```
 
## Shell Commands
 
| Command   | Description                          |
|-----------|--------------------------------------|
| `help`    | List available commands              |
| `clear`   | Clear the terminal screen            |
| `meminfo` | Show RAM and heap usage              |
| `time`    | Show uptime since boot               |
 
## Project Structure
 
```
kernel/
├── boot.asm          # Multiboot entry point, stack setup
├── kernel.cpp        # Kernel main, initialization sequence
├── linker.ld         # Linker script (loads at 2MB)
├── gdt/              # Global Descriptor Table
├── idt/              # Interrupt Descriptor Table
├── isr/              # CPU exception handlers (ISRs 0–31)
├── irq/              # Hardware interrupt handlers (IRQs 0–15)
├── pic/              # 8259 PIC driver
├── pit/              # PIT timer driver
├── pmm/              # Physical memory manager
├── paging/           # Page directory / table setup
├── heap/             # Kernel heap allocator
├── keyboard/         # PS/2 keyboard driver
├── terminal/         # VGA text-mode terminal
├── serial/           # COM1 serial debug output
├── shell/            # Interactive shell
├── panic/            # Kernel panic handler
├── io.h              # inb / outb port I/O
└── string.h          # Minimal string utilities
```
 
## References
 
See [`docs/references.md`](docs/references.md) for links to OSDev wiki articles and Intel SDM sections used in this project.
