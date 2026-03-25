#include "terminal/terminal.h"
#include "serial/serial.h"
#include "gdt.h"

extern "C" void kernel_main()
{

    serial_init();
    serial_write("Kernel booted\n");

    gdt_init();
    serial_write("GDT initialized\n");

    terminal_initialize();
    serial_write("VGA terminal initialized\n");
    terminal_putchar('A');
    terminal_write("\nHello Kernel!");
}
