#include "terminal/terminal.h"
#include "gdt.h"

extern "C" void kernel_main()
{
    gdt_init();

    terminal_initialize();
    terminal_putchar('A');
    terminal_write("\nHello Kernel!");
}
