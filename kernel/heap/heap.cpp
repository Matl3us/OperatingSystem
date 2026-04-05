#include "heap.h"
#include "../panic/panic.h"
#include "../pmm/pmm.h"
#include "../serial/serial.h"
#include <stdint.h>

#define HEAP_PAGES 32

extern uint32_t _kernel_end;

static uintptr_t heap_start;
static uintptr_t position;
static uintptr_t heap_end;

void heap_init()
{
    uintptr_t kernel_end_ptr = (uintptr_t)&_kernel_end;
    heap_start = (kernel_end_ptr + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
    position = heap_start;
    heap_end = heap_start + PAGE_SIZE * HEAP_PAGES;

    serial_write("Heap initialized\n");
    serial_write("Heap start: ");
    serial_write_hex(heap_start);
    serial_putchar('\n');
    serial_write("Heap end: ");
    serial_write_hex(heap_end);
    serial_putchar('\n');
}

void *kmalloc(size_t size)
{
    if (size > heap_end - position)
        kernel_panic("Heap run out of memory");

    uintptr_t pos = position;
    position += size;
    position = (position + 0x3) & ~0x3;

    return (void *)pos;
}

void kfree(void *ptr) { (void)ptr; }
