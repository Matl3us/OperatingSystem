#include "irq.h"
#include "../idt/idt.h"
#include "../pic/pic.h"
#include "../serial/serial.h"

extern "C" void irq_handler(InterruptFrameIRQ *frame)
{
    serial_write("IRQ number: ");
    serial_write_int(frame->irq_number);
    serial_putchar('\n');
    pic_send_eoi(frame->irq_number);
}

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

void irq_init()
{
    idt_set_entry(32, (uint32_t)irq0);
    idt_set_entry(33, (uint32_t)irq1);
    idt_set_entry(34, (uint32_t)irq2);
    idt_set_entry(35, (uint32_t)irq3);
    idt_set_entry(36, (uint32_t)irq4);
    idt_set_entry(37, (uint32_t)irq5);
    idt_set_entry(38, (uint32_t)irq6);
    idt_set_entry(39, (uint32_t)irq7);
    idt_set_entry(40, (uint32_t)irq8);
    idt_set_entry(41, (uint32_t)irq9);
    idt_set_entry(42, (uint32_t)irq10);
    idt_set_entry(43, (uint32_t)irq11);
    idt_set_entry(44, (uint32_t)irq12);
    idt_set_entry(45, (uint32_t)irq13);
    idt_set_entry(46, (uint32_t)irq14);
    idt_set_entry(47, (uint32_t)irq15);
}