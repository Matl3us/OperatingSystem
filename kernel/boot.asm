; Constants declaration for the multiboot header
MAGIC       equ 0x1BADB002
MB_ALIGN    equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MB_ALIGN | MEMINFO
CHECKSUM    equ -(MAGIC + FLAGS)

; Multiboot header declaration
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; BSS section - stack allocation
section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

; Kernel entry point
section .text
global _start
extern kernel_main
_start:
    mov esp, stack_top
    call kernel_main

    cli
.hang:
    hlt
    jmp .hang
