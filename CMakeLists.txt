cmake_minimum_required(VERSION 3.20)

# ── Board selection ───────────────────────────────────────────

# Usage: cmake -DBOARD=esp32-devkit ..
set(BOARD "esp32-devkit" CACHE STRING "Target board")

# ── Map board → arch ─────────────────────────────────────────

include(cmake/boards.cmake)           # sets ARCH based on BOARD
board_to_arch(${BOARD} ARCH)         # e.g. ARCH = avr

# ── Load toolchain before project() ──────────────────────────
set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_SOURCE_DIR}/cmake/toolchain-${ARCH}.cmake"
    CACHE FILEPATH "" FORCE)

project(OpenWarp C ASM)

# ── Collect arch-specific sources ────────────────────────────
file(GLOB ARCH_SOURCES
    "src/arch/${ARCH}/chips/${BOARD}/*.c"
    "src/arch/${ARCH}/chips/${BOARD}/*.S"
)

# ── Build as static library ───────────────────────────────────
add_library(OpenWarp STATIC ${ARCH_SOURCES})

target_include_directories(OpenWarp PUBLIC include/)

# ── Pass board/arch as defines into C ────────────────────────
target_compile_definitions(OpenWarp PUBLIC
    BOARD_${BOARD}
    ARCH_${ARCH}
)

# ── Linker script ─────────────────────────────────────────────
target_link_options(OpenWarp PUBLIC
    -T ${CMAKE_SOURCE_DIR}/linker/${ARCH}-${BOARD}.ld
    -nostdlib
)