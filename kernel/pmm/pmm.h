#pragma once
#include <stdint.h>

#define PAGE_SIZE 4096    // 4KB
#define BITMAP_SIZE 16384 // 512MB RAM

struct MultibootInfo
{
    uint32_t flags; // Bitmask for valid fields in struct
    uint32_t mem_lower;
    uint32_t mem_higher;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_address;
    uint32_t syms[4];
    uint32_t mmap_length;  // Total size in bytes of memory map
    uint32_t mmap_address; // Address of the first memory map entry
} __attribute__((packed));

struct MemMapEntry
{
    uint32_t size;    // Size of this entry
    uint64_t address; // Base address of memory region
    uint64_t length;  // Length of memory region
    uint32_t type;    // 1 means usable RAM
} __attribute__((packed));

void pmm_init(MultibootInfo *mbi);
void *pmm_alloc_page();
void pmm_free_page(void *address);

uint32_t pmm_get_total_pages();
uint32_t pmm_get_free_pages();
uint32_t pmm_get_used_pages();