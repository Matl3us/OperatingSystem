#pragma once
#include <stdint.h>

struct InterruptFrameIRQ
{
    uint32_t edi; // Registers
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t irq_number;
} __attribute__((packed));

void irq_init();