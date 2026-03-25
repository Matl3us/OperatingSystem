#pragma once
#include <stdint.h>

void serial_init();
void serial_putchar(char c);
void serial_write(const char *str);