#include "pit.h"
#include "../io.h"
#include "../serial/serial.h"
#include <stdint.h>

#define chip_freq 1193182
#define frequency 100

uint32_t ticks = 0;

void pit_init()
{
    uint16_t divisor = chip_freq / frequency;
    uint8_t cmdByte = 0x36;
    outb(0x43, cmdByte);

    uint8_t low_byte = divisor & 0xFF;
    uint8_t high_byte = divisor >> 8;
    outb(0x40, low_byte);
    outb(0x40, high_byte);
}

void pit_handler()
{
    ticks++;
    if (ticks % 100 == 0)
    {
        serial_write("Ticks: ");
        serial_write_int(ticks);
        serial_putchar('\n');
    }
}
