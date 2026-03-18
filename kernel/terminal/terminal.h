#pragma once
#include <stdint.h>
#include <stddef.h>

static uint8_t BLACK_COLOR = 0;
static uint8_t WHITE_COLOR = 15;

void terminal_initialize();
void terminal_putchar(char c, uint8_t fg = WHITE_COLOR, uint8_t bg = BLACK_COLOR);
void terminal_write(const char *data, uint8_t fg = WHITE_COLOR, uint8_t bg = BLACK_COLOR);