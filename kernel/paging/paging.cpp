#include "paging.h"
#include <stdint.h>

#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITABLE (1 << 1)

static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t page_table[1024] __attribute__((aligned(4096)));

void paging_init()
{
    for (int i = 0; i < 1024; i++)
        page_directory[i] = 0;

    for (int i = 0; i < 1024; i++)
        page_table[i] = (i * 0x1000) | PAGE_PRESENT | PAGE_WRITABLE;

    page_directory[0] = (uintptr_t)page_table | PAGE_PRESENT | PAGE_WRITABLE;

    asm volatile("mov %0, %%cr3" ::"r"(page_directory));

    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 |= (1 << 31);
    asm volatile("mov %0, %%cr0" ::"r"(cr0));
}
