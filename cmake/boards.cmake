function(board_to_arch BOARD OUT_ARCH)
    if(BOARD STREQUAL "esp32-devkit" OR BOARD STREQUAL "esp32s3")
        set(${OUT_ARCH} "esp32" PARENT_SCOPE)

    elseif(BOARD STREQUAL "atmega328p" OR BOARD STREQUAL "attiny85")
        set(${OUT_ARCH} "avr" PARENT_SCOPE)

    elseif(BOARD STREQUAL "stm32f4" OR
           BOARD STREQUAL "rp2040"  OR
           BOARD STREQUAL "nrf52840")
        set(${OUT_ARCH} "arm-cm4" PARENT_SCOPE)

    else()
        message(FATAL_ERROR "Unknown board: ${BOARD}. Add it to cmake/boards.cmake")
    endif()
endfunction()