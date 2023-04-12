cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_STANDARD 11)
set(DRV_NAME picodisplay-c-driver)

include(lib/pico-sdk/pico_sdk_init.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${DRV_NAME})

add_library(${DRV_NAME} INTERFACE)
pico_sdk_init()

target_link_libraries(${DRV_NAME} INTERFACE
  pico_stdlib
  hardware_spi
  hardware_pwm
)

add_subdirectory(src)
add_subdirectory(example)