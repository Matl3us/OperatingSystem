#include "isr.h"
#include "idt.h"
#include "serial/serial.h"

static const char *exception_names[] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",
    "x87 floating point",
    "Alignment check",
    "Machine check",
    "SIMD floating point",
    "Virtualization",
    "Control protection",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

extern "C" void isr_handler(InterruptFrame *frame)
{
    serial_write("Exception: ");
    serial_write(exception_names[frame->exception_number]);
    serial_putchar('\n');
    while (true)
        ;
}

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

void isr_init()
{
    idt_set_entry(0, (uint32_t)isr0);
    idt_set_entry(1, (uint32_t)isr1);
    idt_set_entry(2, (uint32_t)isr2);
    idt_set_entry(3, (uint32_t)isr3);
    idt_set_entry(4, (uint32_t)isr4);
    idt_set_entry(5, (uint32_t)isr5);
    idt_set_entry(6, (uint32_t)isr6);
    idt_set_entry(7, (uint32_t)isr7);
    idt_set_entry(8, (uint32_t)isr8);
    idt_set_entry(9, (uint32_t)isr9);
    idt_set_entry(10, (uint32_t)isr10);
    idt_set_entry(11, (uint32_t)isr11);
    idt_set_entry(12, (uint32_t)isr12);
    idt_set_entry(13, (uint32_t)isr13);
    idt_set_entry(14, (uint32_t)isr14);
    idt_set_entry(15, (uint32_t)isr15);
    idt_set_entry(16, (uint32_t)isr16);
    idt_set_entry(17, (uint32_t)isr17);
    idt_set_entry(18, (uint32_t)isr18);
    idt_set_entry(19, (uint32_t)isr19);
    idt_set_entry(20, (uint32_t)isr20);
    idt_set_entry(21, (uint32_t)isr21);
    idt_set_entry(22, (uint32_t)isr22);
    idt_set_entry(23, (uint32_t)isr23);
    idt_set_entry(24, (uint32_t)isr24);
    idt_set_entry(25, (uint32_t)isr25);
    idt_set_entry(26, (uint32_t)isr26);
    idt_set_entry(27, (uint32_t)isr27);
    idt_set_entry(28, (uint32_t)isr28);
    idt_set_entry(29, (uint32_t)isr29);
    idt_set_entry(30, (uint32_t)isr30);
    idt_set_entry(31, (uint32_t)isr31);

    idt_flush_now();
}