# 0. erase previous

sudo rm -rf binaries/myproject

mkdir binaries/myproject

# ── 1. Compile startup.S ──────────────────────────────────────
./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -mlongcalls -mtext-section-literals \
    -ffreestanding -nostdlib \
    -ffunction-sections -fdata-sections \
    -c src/arch/xtensa-lx6/chips/esp32/startup.S -o binaries/myproject/startup.o

# ── 2. Compile gpio.c ─────────────────────────────────────────
./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -mlongcalls -mtext-section-literals \
    -ffreestanding -nostdlib \
    -ffunction-sections -fdata-sections \
    -Iinclude -std=gnu11 -O1 \
    -c src/arch/xtensa-lx6/chips/esp32/gpio.c -o binaries/myproject/gpio.o

# ── 3. Compile timing.c ───────────────────────────────────────
./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -mlongcalls -mtext-section-literals \
    -ffreestanding -nostdlib \
    -ffunction-sections -fdata-sections \
    -Iinclude -std=gnu11 -O1 \
    -c src/arch/xtensa-lx6/chips/esp32/timing.c -o binaries/myproject/timing.o

# ── 4. Compile uart.c ─────────────────────────────────────────
./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -mlongcalls -mtext-section-literals \
    -ffreestanding -nostdlib \
    -ffunction-sections -fdata-sections \
    -Iinclude -std=gnu11 -O1 \
    -c src/arch/xtensa-lx6/chips/esp32/uart.c -o binaries/myproject/uart.o

./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -mlongcalls -mtext-section-literals \
    -ffreestanding -nostdlib \
    -ffunction-sections -fdata-sections \
    -Iinclude -std=gnu11 -O1 \
    -c src/arch/xtensa-lx6/chips/esp32/watchdog.c -o binaries/myproject/watchdog.o

# ── 5. Compile main.c ─────────────────────────────────────────
./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -mlongcalls -mtext-section-literals \
    -ffreestanding -nostdlib \
    -ffunction-sections -fdata-sections \
    -Iinclude -std=gnu11 -O1 \
    -c examples/SerialTest/SerialTest.c -o binaries/myproject/main.o

# ── 6. Link ───────────────────────────────────────────────────
./tools/esp32/bin/xtensa-esp32-elf-gcc \
    -nostdlib \
    -T src/arch/xtensa-lx6/chips/esp32/linker.ld \
    -Wl,--gc-sections \
    -Wl,-Map=firmware.map \
    binaries/myproject/startup.o binaries/myproject/gpio.o binaries/myproject/timing.o binaries/myproject/uart.o binaries/myproject/watchdog.o binaries/myproject/main.o \
    -o binaries/myproject/firmware.elf

# ── 7. Convert ELF → flash binary ────────────────────────────
esptool --chip esp32 elf2image \
    --flash-mode dio \
    --flash-freq 40m \
    --flash-size 4MB \
    -o binaries/myproject/firmware.bin binaries/myproject/firmware.elf

# ── 8. Flash ──────────────────────────────────────────────────
esptool --chip esp32 --port /dev/ttyUSB0 --baud 115200 \
    write-flash 0x1000 binaries/myproject/firmware.bin
