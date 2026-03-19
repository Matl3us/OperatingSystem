#include "gdt.h"

#define GDT_ENTRIES 3

static GDTEntry gdt[GDT_ENTRIES];
static GDTPointer gdt_ptr;

extern "C" void gdt_flush(uint32_t);

static void gdt_set(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt[index].base_low = (base & 0xFFFF);
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = (limit & 0xFFFF);
    gdt[index].granularity = (limit >> 16) & 0x0F;

    gdt[index].granularity |= (granularity & 0xF0);
    gdt[index].access = access;
}

void gdt_init()
{
    gdt_ptr.limit = (sizeof(GDTEntry) * GDT_ENTRIES) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    gdt_set(0, 0, 0x00000, 0x00, 0x00);
    gdt_set(1, 0, 0xFFFFF, 0x9A, 0xCF);
    gdt_set(2, 0, 0xFFFFF, 0x92, 0xCF);

    gdt_flush((uint32_t)&gdt_ptr);
}
