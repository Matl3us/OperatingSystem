#include "pic.h"
#include "../io.h"

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21

#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

void io_wait() { outb(0x80, 0x00); }

void pic_init()
{
    outb(PIC1_CMD, 0x11);
    io_wait();
    outb(PIC2_CMD, 0x11);
    io_wait();

    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    outb(PIC1_DATA, 0xFE);
    outb(PIC2_DATA, 0xFF);
}

void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8)
    {
        outb(PIC2_CMD, 0x20);
    }
    outb(PIC1_CMD, 0x20);
}
