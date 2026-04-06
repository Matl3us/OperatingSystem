#include "shell.h"
#include "../pit/pit.h"
#include "../pmm/pmm.h"
#include "../heap/heap.h"
#include "../string.h"
#include "../terminal/terminal.h"
#include <stdint.h>

static char input_buffer[256];
static uint8_t input_len = 0;

void shell_execute(const char *cmd)
{
    if (str_compare(cmd, "help"))
    {
        terminal_write("Available commands are:\n");
        terminal_write("- help\n");
        terminal_write("- clear\n");
        terminal_write("- meminfo\n");
        terminal_write("- time\n");
    }
    else if (str_compare(cmd, "clear"))
    {
        terminal_clear();
    }
    else if (str_compare(cmd, "meminfo"))
    {
        uint32_t total = pmm_get_total_pages() * PAGE_SIZE / 1024;
        uint32_t used = pmm_get_used_pages() * PAGE_SIZE / 1024;
        uint32_t free = pmm_get_free_pages() * PAGE_SIZE / 1024;

        uint32_t heap_total = heap_get_pages() * PAGE_SIZE / 1024;
        uint32_t heap_used = heap_get_used_bytes();

        terminal_write("Total RAM : ");
        terminal_write_int(total);
        terminal_write(" KB\n");
        terminal_write("Used      : ");
        terminal_write_int(used);
        terminal_write(" KB\n");
        terminal_write("Free      : ");
        terminal_write_int(free);
        terminal_write(" KB\n\n");

        terminal_write("Total heap size : ");
        terminal_write_int(heap_total);
        terminal_write(" KB\n");
        terminal_write("Heap used       : ");
        terminal_write_int(heap_used);
        terminal_write(" bytes\n");
    }
    else if (str_compare(cmd, "time"))
    {
        uint32_t seconds = ticks / 100;
        uint32_t minutes = seconds / 60;
        uint32_t hours = minutes / 60;

        terminal_write("Time since the start of the OS: ");
        if (hours > 0)
        {
            terminal_write_int(hours);
            terminal_write("h ");
        }
        if (minutes > 0)
        {
            terminal_write_int(minutes % 60);
            terminal_write("min ");
        }
        terminal_write_int(seconds % 60);
        terminal_write("s\n");
    }
    else
    {
        terminal_write("Invalid command: ");
        terminal_write(cmd);
        terminal_putchar('\n');
    }
}

void shell_handle_char(char c)
{
    if (input_len + 1 >= 256)
        return;

    if (c == '\n')
    {
        input_buffer[input_len] = '\0';
        shell_execute(input_buffer);
        input_len = 0;
        return;
    }

    if (c == '\b')
    {
        if (input_len > 0)
            input_len--;
        return;
    }

    input_buffer[input_len++] = c;
}
