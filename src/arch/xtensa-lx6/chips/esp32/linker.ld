ENTRY(_start)

MEMORY
{
    iram0_0_seg  (RX)  : ORIGIN = 0x40080000, LENGTH = 0x20000
    dram0_0_seg  (RW)  : ORIGIN = 0x3FFB0000, LENGTH = 0x40000
    rtc_iram_seg (RX)  : ORIGIN = 0x400C0000, LENGTH = 0x2000
    rtc_data_seg (RW)  : ORIGIN = 0x3FF80000, LENGTH = 0x2000
}

_stack_size = 0x2000;

SECTIONS
{
    .vectors :
    {
        KEEP(*(.vectors))
        KEEP(*(.vectors.*))
    } > iram0_0_seg

    .text :
    {
        _text_start = .;
        *(.literal .literal.*)
        *(.text .text.*)
        _text_end = .;
    } > iram0_0_seg

    .rodata :
    {
        _rodata_start = .;
        *(.rodata .rodata.*)
        *(.rodata1)
        . = ALIGN(4);
        _rodata_end = .;
    } > dram0_0_seg

    .data :
    {
        _data_start = .;
        *(.data .data.*)
        *(.gnu.linkonce.d.*)
        . = ALIGN(4);
        _data_end = .;
    } > dram0_0_seg

    .bss (NOLOAD) :
    {
        _bss_start = .;
        *(.bss .bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } > dram0_0_seg

    .stack (NOLOAD) :
    {
        . = ALIGN(16);
        _stack_bottom = .;
        . += _stack_size;
        _stack_top = .;
    } > dram0_0_seg

    /DISCARD/ :
    {
        *(.xt.prop .xt.prop.*)
        *(.gnu.attributes)
        *(.comment)
        *(.note*)
    }
}

PROVIDE(_bss_start  = _bss_start);
PROVIDE(_bss_end    = _bss_end);
PROVIDE(_stack_top  = _stack_top);
