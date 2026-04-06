#pragma once
#include <stddef.h>
#include <stdint.h>

void heap_init();
void *kmalloc(size_t size);
void kfree(void *ptr);

uint32_t heap_get_pages();
size_t heap_get_used_bytes();