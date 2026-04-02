#pragma once
#include <stdint.h>

extern uint32_t ticks;

void pit_init();
void pit_handler();
