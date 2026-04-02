[bits 32]

global irq0 ; IRQ handlers
irq0:
    push dword 0
    jmp irq_common

global irq1
irq1:
    push dword 1
    jmp irq_common

global irq2
irq2:
    push dword 2
    jmp irq_common

global irq3
irq3:
    push dword 3
    jmp irq_common

global irq4
irq4:
    push dword 4
    jmp irq_common

global irq5
irq5:
    push dword 5
    jmp irq_common

global irq6
irq6:
    push dword 6
    jmp irq_common

global irq7
irq7:
    push dword 7
    jmp irq_common

global irq8
irq8:
    push dword 8
    jmp irq_common

global irq9
irq9:
    push dword 9
    jmp irq_common

global irq10
irq10:
    push dword 10
    jmp irq_common

global irq11
irq11:
    push dword 11
    jmp irq_common

global irq12
irq12:
    push dword 12
    jmp irq_common

global irq13
irq13:
    push dword 13
    jmp irq_common

global irq14
irq14:
    push dword 14
    jmp irq_common

global irq15
irq15:
    push dword 15
    jmp irq_common

extern irq_handler
irq_common:
    pusha
    push esp

    call irq_handler 

    add esp, 4
    popa
    add esp, 4

    iret
