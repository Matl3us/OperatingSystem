#include "pmm.h"
#include "../serial/serial.h"
#include <stdint.h>

#define PAGE_SIZE 4096    // 4KB
#define BITMAP_SIZE 16384 // 512MB RAM
static uint8_t bitmap[BITMAP_SIZE];
extern uint32_t _kernel_end;

void pmm_init(MultibootInfo *mbi)
{
    if (!((mbi->flags >> 6) & 1))
    {
        serial_write("Invalid memory map\n");
        while (true)
            ;
    }

    for (int i = 0; i < BITMAP_SIZE; i++)
        bitmap[i] = 0;

    uintptr_t mem_address = mbi->mmap_address;
    for (uint32_t size = 0; size < mbi->mmap_length;)
    {
        MemMapEntry *entry = (MemMapEntry *)(mem_address + size);

        if (entry->type == 1)
        {
            int firstPage = entry->address / PAGE_SIZE;
            int pagesCount = entry->length / PAGE_SIZE;
            for (int i = firstPage; i < firstPage + pagesCount; i++)
            {
                bitmap[i / 8] |= (1 << (i % 8));
            }
        }

        size += entry->size + 4;
    }

    uintptr_t kernel_end_ptr = (uintptr_t)&_kernel_end;
    int kernel_used_pages = kernel_end_ptr / PAGE_SIZE;
    for (int i = 0; i < kernel_used_pages; i++)
        bitmap[i / 8] &= ~(1 << (i % 8));
}

void *pmm_alloc_page()
{
    for (int page = 0; page < BITMAP_SIZE; page++)
    {
        for (int bit = 0; bit < 8; bit++)
        {
            if ((bitmap[page] >> bit) & 1)
            {
                bitmap[page] &= ~(1 << bit);
                return (void *)((uintptr_t)(page * 8 + bit) * PAGE_SIZE);
            }
        }
    }
    return nullptr;
}

void pmm_free_page(void *address)
{
    int page = (uintptr_t)address / PAGE_SIZE;
    bitmap[page / 8] |= (1 << (page % 8));
}
