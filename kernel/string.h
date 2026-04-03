#pragma once
#include <stdint.h>

static inline bool str_compare(const char *a, const char *b)
{
    uint8_t i;
    for (i = 0; a[i] != '\0'; i++)
    {
        if (a[i] != b[i])
            return false;
    }

    if (b[i] != '\0')
        return false;

    return true;
}
