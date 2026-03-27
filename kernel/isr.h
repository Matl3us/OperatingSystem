#pragma once
#include <stdint.h>

struct InterruptFrame
{
    uint32_t edi; // Registers
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t exception_number;
    uint32_t error_code;
} __attribute__((packed));

void isr_init();