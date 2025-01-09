cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(pico_sdk_import.cmake)

# Setup common to both versions

# Initialize the SDK
pico_sdk_init()

add_subdirectory(../../third-party/pi-pico-adafruit-neopixels/pico_neopixels build)

# The Plasma 2040 version
set(PLASMA pimoroni-plasma-rainbow-2040)

project(${PLASMA} C CXX ASM)
set(${PLASMA} PICO_BOARD pimoroni_plasma_2040)

# Add your source files
add_executable(${PLASMA}
    src/plasma.cpp
)

# Link required libraries
target_link_libraries(${PLASMA} LINK_PUBLIC
    pico_stdlib
    pico_neopixel
    pico_bootsel_via_double_reset
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PLASMA})

# Disable USB serial and enable UART serial
pico_enable_stdio_usb(${PLASMA} 0)
pico_enable_stdio_uart(${PLASMA} 1)

# The Plasma 2350 version
set(PLASMA_2 pimoroni-plasma-rainbow-2350)

project(${PLASMA_2} C CXX ASM)
set(${PLASMA_2} PICO_BOARD pimoroni_plasma_2350)

# Add your source files
add_executable(${PLASMA_2}
    src/plasma.cpp
)

# Link required libraries
target_link_libraries(${PLASMA_2} LINK_PUBLIC
    pico_stdlib
    pico_neopixel
    pico_bootsel_via_double_reset
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PLASMA_2})

# Disable USB serial and enable UART serial
pico_enable_stdio_usb(${PLASMA_2} 0)
pico_enable_stdio_uart(${PLASMA_2} 1)

# Set up files for the release packages for both projects.
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PLASMA}.uf2
    ${CMAKE_CURRENT_BINARY_DIR}/${PLASMA_2}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)


