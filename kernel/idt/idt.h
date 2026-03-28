#pragma once
#include <stdint.h>

struct IDTEntry
{
    uint16_t base_low;  // Handler address low
    uint16_t selector;  // Segment selector
    uint8_t always0;    // Zero
    uint8_t flags;      // Type and attribute flags
    uint16_t base_high; // Handler address high
} __attribute__((packed));

struct IDTPointer
{
    uint16_t size;    // Size of the IDT table minus 1
    uint32_t address; // Linear address to the table
} __attribute__((packed));

void idt_init();
void idt_set_entry(int index, uint32_t address);
void idt_flush_now();