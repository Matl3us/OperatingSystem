#include "serial.h"
#include "../io.h"

#define COM1 0x3F8

void serial_init()
{
    outb(COM1 + 1, 0x00); // Disable interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03); // Baud rate low byte: 38400 baud
    outb(COM1 + 1, 0x00); // Baud rate high byte
    outb(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7); // Enable FIFO
    outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

static int serial_is_ready()
{
    return inb(COM1 + 5) & 0x20;
}

void serial_putchar(char c)
{
    while (!serial_is_ready())
        ;
    outb(COM1, c);
}

void serial_write(const char *str)
{
    while (*str)
    {
        serial_putchar(*str++);
    }
}

void serial_write_int(uint32_t n)
{
    if (n == 0)
        serial_putchar('0');

    char buffer[10];
    int idx = 0;
    while (n > 0)
    {
        buffer[idx++] = (n % 10) + '0';
        n /= 10;
    }

    idx -= 1;
    while (idx >= 0)
    {
        serial_putchar(buffer[idx--]);
    }
}