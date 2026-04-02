#include "terminal.h"
#include "../io.h"
#include <cstdint>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_START = (uint16_t *)0xB8000;

static size_t terminal_row;
static size_t terminal_col;
static uint8_t terminal_color;

uint8_t calculate_color(uint8_t fg, uint8_t bg) { return fg | bg << 4; }

uint16_t calculate_char(char c, uint8_t color)
{
    return (uint16_t)c | (uint16_t)color << 8;
}

void terminal_initialize()
{
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = calculate_color(WHITE_COLOR, BLACK_COLOR);
}

void terminal_update_cursor()
{
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_col;
    uint8_t low_byte = pos & 0xFF;
    uint8_t high_byte = pos >> 8;

    outb(0x3D4, 0x0F);
    outb(0x3D5, low_byte);
    outb(0x3D4, 0x0E);
    outb(0x3D5, high_byte);
}

void terminal_putchar(char c, uint8_t fg, uint8_t bg)
{
    if (c == '\n')
    {
        terminal_col = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
        terminal_update_cursor();
        return;
    }

    if (c == '\t')
    {
        terminal_col += 4 - (terminal_col % 4);
        if (terminal_col > VGA_WIDTH)
            terminal_col = VGA_WIDTH;
        terminal_update_cursor();
        return;
    }

    if (c == '\b')
    {
        if (terminal_col > 0)
        {
            terminal_col--;
            uint16_t *address =
                VGA_START + (terminal_row * VGA_WIDTH + terminal_col);
            uint8_t color = calculate_color(fg, bg);
            *address = calculate_char(' ', color);
        }
        terminal_update_cursor();
        return;
    }

    uint16_t *address = VGA_START + (terminal_row * VGA_WIDTH + terminal_col);
    uint8_t color = calculate_color(fg, bg);
    *address = calculate_char(c, color);

    if (++terminal_col == VGA_WIDTH)
    {
        terminal_col = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
    terminal_update_cursor();
}

void terminal_write(const char *data, uint8_t fg, uint8_t bg)
{
    for (size_t i = 0; data[i] != '\0'; i++)
    {
        terminal_putchar(data[i], fg, bg);
    }
}
