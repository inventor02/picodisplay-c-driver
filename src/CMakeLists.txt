target_sources(${DRV_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/st7789_spi.c
  ${CMAKE_CURRENT_LIST_DIR}/pico_display.c
)

target_include_directories(${DRV_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)