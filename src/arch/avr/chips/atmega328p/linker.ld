MEMORY { flash (rx) : ORIGIN = 0x0000, LENGTH = 32K }
SECTIONS {
    .text : { *(.text) } > flash
    .data : { *(.data) } > flash
    .bss  : { *(.bss) }
}