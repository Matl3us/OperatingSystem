#include "shell.h"
#include "../pit/pit.h"
#include "../string.h"
#include "../terminal/terminal.h"
#include <stdint.h>

static char input_buffer[256];
static uint8_t input_len = 0;

void shell_execute(const char *cmd)
{
    if (str_compare(cmd, "help"))
    {
        terminal_write("Available commands are: help, clear and info\n");
    }
    else if (str_compare(cmd, "clear"))
    {
        terminal_clear();
    }
    else if (str_compare(cmd, "info"))
    {
        terminal_write("Time since the start of the OS: ");
        terminal_write_int(ticks / 100);
        terminal_write(" s\n");
    }
    else
    {
        terminal_write("Invalid command: ");
        terminal_write(cmd);
        terminal_write("\nAvailable commands are: help, clear and info\n");
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
