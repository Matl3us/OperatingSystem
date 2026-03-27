[bits 32]
global idt_flush

idt_flush:
    mov eax, [esp + 4]  ; Get IDTPointer address passed as argument
    lidt [eax]          ; Load it into CPU's register
    ret