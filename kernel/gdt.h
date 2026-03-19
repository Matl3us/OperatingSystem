#pragma once
#include <stdint.h>

struct GDTEntry
{
    uint16_t limit_low;  // Segment limit low
    uint16_t base_low;   // Base address low
    uint8_t base_middle; // Base address middle
    uint8_t access;      // Access flags
    uint8_t granularity; // Segment limit high + flags
    uint8_t base_high;   // Base address high
} __attribute__((packed));

struct GDTPointer
{
    uint16_t limit; // Size of the GDT in bytes minus 1
    uint32_t base;  // Address of the GDT
} __attribute__((packed));

void gdt_init();