# OS Dev References

## Multiboot Specification

-  https://www.gnu.org/software/grub/manual/multiboot/multiboot.html

### Header Constants

| Constant | Value | Purpose |
|---|---|---|
| `MAGIC` | `0x1BADB002` | Fixed value GRUB searches for in binary |
| `MB_ALIGN` | `1<<0` (= 1) | Bit 0 — tells GRUB to align loaded modules to 4KB page boundaries |
| `MEMINFO` | `1<<1` (= 2) | Bit 1 — tells GRUB to provide a memory map (how much RAM exists) |
| `FLAGS` | `ALIGN \| MEMINFO` (= 3) | Combined flags field sent to GRUB |
| `CHECKSUM` | `-(MAGIC + FLAGS)` | Must satisfy: MAGIC + FLAGS + CHECKSUM == 0 |

## Global Descriptor Table

- https://wiki.osdev.org/Global_Descriptor_Table
- https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html

## Interrupt Descriptor Table

- https://wiki.osdev.org/Interrupt_Descriptor_Table

## Programmable Interrupt Controller

- https://wiki.osdev.org/8259_PIC

## Programmable Interval Timer

- https://wiki.osdev.org/Programmable_Interval_Timer

## Keyboard Driver

- http://wiki.osdev.org/PS/2_Keyboard
