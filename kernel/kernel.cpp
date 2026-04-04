#include "gdt/gdt.h"
#include "idt/idt.h"
#include "irq/irq.h"
#include "isr/isr.h"
#include "paging/paging.h"
#include "pic/pic.h"
#include "pit/pit.h"
#include "pmm/pmm.h"
#include "serial/serial.h"
#include "terminal/terminal.h"
#include <stdint.h>

extern "C" void kernel_main(uint32_t magic, MultibootInfo *mbi)
{
    if (magic != 0x2BADB002)
        asm volatile("hlt");

    serial_init();
    serial_write("Kernel booted\n");

    gdt_init();
    serial_write("GDT initialized\n");

    idt_init();
    serial_write("IDT initialized\n");

    pic_init();
    serial_write("PIC initialized\n");

    isr_init();
    serial_write("ISR initialized\n");

    irq_init();
    serial_write("IRQ initialized\n");

    idt_flush_now();
    serial_write("IDT flushed\n");

    pmm_init(mbi);
    serial_write("PMM initialized\n");

    paging_init();
    serial_write("Paging initialized\n");

    pit_init();
    serial_write("PIT initialized\n");

    asm volatile("sti");

    terminal_initialize();
    serial_write("VGA terminal initialized\n");

    terminal_write("Hello Kernel!\n");

    while (true)
    {
        asm volatile("hlt");
    }
}
