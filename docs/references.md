# OS Dev References

## Multiboot Specification

**Source:** https://www.gnu.org/software/grub/manual/multiboot/multiboot.html

### Header Constants

| Constant | Value | Purpose |
|---|---|---|
| `MAGIC` | `0x1BADB002` | Fixed value GRUB searches for in binary |
| `MB_ALIGN` | `1<<0` (= 1) | Bit 0 — tells GRUB to align loaded modules to 4KB page boundaries |
| `MEMINFO` | `1<<1` (= 2) | Bit 1 — tells GRUB to provide a memory map (how much RAM exists) |
| `FLAGS` | `ALIGN \| MEMINFO` (= 3) | Combined flags field sent to GRUB |
| `CHECKSUM` | `-(MAGIC + FLAGS)` | Must satisfy: MAGIC + FLAGS + CHECKSUM == 0 |