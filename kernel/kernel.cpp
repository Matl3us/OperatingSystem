#include "terminal/terminal.h"
#include "serial/serial.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "isr/isr.h"

extern "C" void kernel_main()
{
    serial_init();
    serial_write("Kernel booted\n");

    gdt_init();
    serial_write("GDT initialized\n");

    idt_init();
    serial_write("IDT initialized\n");

    isr_init();
    serial_write("ISR initialized\n");

    terminal_initialize();
    serial_write("VGA terminal initialized\n");

    terminal_write("Hello Kernel!\n");
}