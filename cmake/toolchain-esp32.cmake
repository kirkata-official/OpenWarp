set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR xtensa)

set(CMAKE_C_COMPILER   xtensa-esp32-elf-gcc)
set(CMAKE_ASM_COMPILER xtensa-esp32-elf-gcc)
set(CMAKE_OBJCOPY      xtensa-esp32-elf-objcopy)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

add_compile_options(-mlongcalls -mtext-section-literals -ffreestanding -nostdlib)