set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER   avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_OBJCOPY      avr-objcopy)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU set per-board via BOARD define, e.g. -mmcu=atmega328p
add_compile_options(-ffreestanding -nostdlib)