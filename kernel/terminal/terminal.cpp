#include "terminal.h"
#include "../io.h"
#include <stdint.h>

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

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void terminal_initialize()
{
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = calculate_color(WHITE_COLOR, BLACK_COLOR);
    terminal_enable_cursor(1, 15);
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
    switch (c)
    {
        case '\n':
            terminal_col = 0;
            if (++terminal_row == VGA_HEIGHT)
            {
                terminal_row = 0;
                terminal_clear();
            }
            break;
        case '\t':
            terminal_col += 4 - (terminal_col % 4);
            if (terminal_col > VGA_WIDTH)
                terminal_col = VGA_WIDTH;
            break;
        case '\b':
            if (terminal_col > 0)
            {
                terminal_col--;
                uint16_t *address =
                    VGA_START + (terminal_row * VGA_WIDTH + terminal_col);
                uint8_t color = calculate_color(fg, bg);
                *address = calculate_char(' ', color);
            }
            break;
        default:
            uint16_t *address =
                VGA_START + (terminal_row * VGA_WIDTH + terminal_col);
            uint8_t color = calculate_color(fg, bg);
            *address = calculate_char(c, color);

            if (++terminal_col == VGA_WIDTH)
            {
                terminal_col = 0;
                if (++terminal_row == VGA_HEIGHT)
                    terminal_row = 0;
            }
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

void terminal_write_int(uint32_t n)
{
    if (n == 0)
        terminal_putchar('0');

    char buffer[10];
    int idx = 0;
    while (n > 0)
    {
        buffer[idx++] = (n % 10) + '0';
        n /= 10;
    }

    idx -= 1;
    while (idx >= 0)
    {
        terminal_putchar(buffer[idx--]);
    }
}

void terminal_clear()
{

    for (uint16_t i = 0; i < VGA_HEIGHT; i++)
    {
        for (uint16_t j = 0; j < VGA_WIDTH; j++)
        {
            uint16_t *address = VGA_START + (i * VGA_WIDTH + j);
            uint8_t color = calculate_color(WHITE_COLOR, BLACK_COLOR);
            *address = calculate_char(' ', color);
        }
    }
    terminal_col = 0;
    terminal_row = 0;
    terminal_update_cursor();
}
