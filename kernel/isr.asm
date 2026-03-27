[bits 32]

global isr0 ; Division by zero
isr0:
    push byte 0 ; Dummy error code
    push byte 0 ; Exception number
    jmp isr_common

global isr1 ; Debug 
isr1:
    push byte 0 
    push byte 1
    jmp isr_common

global isr2 ; Non-maskable interrupt 
isr2:
    push byte 0
    push byte 2
    jmp isr_common

global isr3 ; Breakpoint
isr3:
    push byte 0
    push byte 3
    jmp isr_common

global isr4 ; Overflow
isr4:
    push byte 0
    push byte 4
    jmp isr_common

global isr5 ; Bound range exceeded
isr5:
    push byte 0
    push byte 5
    jmp isr_common

global isr6 ; Invalid opcode
isr6:
    push byte 0
    push byte 6
    jmp isr_common

global isr7 ; Device not available
isr7:
    push byte 0
    push byte 7
    jmp isr_common

global isr8 ; Double fault
isr8:
    push byte 8
    jmp isr_common

global isr9 ; Coprocessor segment overrun
isr9:
    push byte 0
    push byte 9
    jmp isr_common

global isr10 ; Invalid TSS
isr10:
    push byte 10
    jmp isr_common

global isr11 ; Segment not present
isr11:
    push byte 11
    jmp isr_common

global isr12 ; Stack segment fault
isr12:
    push byte 12
    jmp isr_common

global isr13 ; General protection fault
isr13:
    push byte 13
    jmp isr_common

global isr14 ; Page fault
isr14:
    push byte 14
    jmp isr_common

global isr15 ; Reserved
isr15:
    push byte 0
    push byte 15
    jmp isr_common

global isr16 ; x87 floating point
isr16:
    push byte 0
    push byte 16
    jmp isr_common

global isr17 ; Alignment check
isr17:
    push byte 17
    jmp isr_common

global isr18 ; Machine check
isr18:
    push byte 0
    push byte 18
    jmp isr_common

global isr19 ; SIMD floating point
isr19:
    push byte 0
    push byte 19
    jmp isr_common

global isr20 ; Virtualization
isr20:
    push byte 0
    push byte 20
    jmp isr_common

global isr21 ; Control protection
isr21:
    push byte 21
    jmp isr_common

global isr22 ; Reserved
isr22:
    push byte 0
    push byte 22
    jmp isr_common

global isr23 ; Reserved
isr23:
    push byte 0
    push byte 23
    jmp isr_common

global isr24 ; Reserved
isr24:
    push byte 0
    push byte 24
    jmp isr_common

global isr25 ; Reserved
isr25:
    push byte 0
    push byte 25
    jmp isr_common

global isr26 ; Reserved
isr26:
    push byte 0
    push byte 26
    jmp isr_common

global isr27 ; Reserved
isr27:
    push byte 0
    push byte 27
    jmp isr_common

global isr28 ; Reserved
isr28:
    push byte 0
    push byte 28
    jmp isr_common

global isr29 ; Reserved
isr29:
    push byte 0
    push byte 29
    jmp isr_common

global isr30 ; Reserved
isr30:
    push byte 0
    push byte 30
    jmp isr_common

global isr31 ; Reserved
isr31:
    push byte 0
    push byte 31
    jmp isr_common

extern isr_handler
isr_common:
    pusha

    push esp
    call isr_handler
    add esp, 4

    popa
    iret