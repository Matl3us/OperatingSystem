#include "idt.h"

#define IDT_ENTRIES 256

static IDTEntry idt[IDT_ENTRIES];
static IDTPointer idt_ptr;

extern "C" void idt_flush(uint32_t);

void idt_set_entry(int index, uint32_t address)
{
    idt[index].base_low = (address & 0xFFFF);
    idt[index].selector = 0x08;
    idt[index].always0 = 0;
    idt[index].flags = 0x8E;
    idt[index].base_high = address >> 16;
}

void idt_flush_now()
{
    idt_flush((uint32_t)&idt_ptr);
}

void idt_init()
{
    idt_ptr.size = (sizeof(IDTEntry) * IDT_ENTRIES) - 1;
    idt_ptr.address = (uint32_t)&idt;
}