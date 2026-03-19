[bits 32]
global gdt_flush

gdt_flush:
    mov eax, [esp + 4]  ; Get GDTPointer address passed as argument
    lgdt [eax]          ; load it into the CPU's GDT register

    mov ax, 0x10        ; 0x10 - entry 2 (Kernel data segment) 
    mov ds, ax          ; Reload data segment registers
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush     ; Jump to 0x08 - entry 1 (Kernel code segment)

.flush:
    ret