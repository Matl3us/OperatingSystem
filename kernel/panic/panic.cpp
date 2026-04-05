#include "panic.h"
#include "../serial/serial.h"

void kernel_panic(const char *message)
{
    serial_write("\nKERNEL PANIC!");
    serial_write(message);
    serial_putchar('\n');
    while (true)
        ;
}
