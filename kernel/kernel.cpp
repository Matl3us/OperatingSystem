#include "terminal/terminal.h"

extern "C" void kernel_main()
{
    terminal_initialize();
    terminal_putchar('A');
    terminal_write("\nHello Kernel!");
}
