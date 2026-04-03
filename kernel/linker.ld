/* Entry point */
ENTRY(_start)

SECTIONS
{
    /* Placing from 2MB onwards */
    . = 2M;

    /* Placing multiboot header and executable code in memory */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Placing constant, read-only data in memory */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Placing initialized variables data in memory */ 
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Placing uninitialized variables and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    _kernel_end = .;
}
