set(EXAMPLE_NAME ${DRV_NAME}-example)

add_executable(${EXAMPLE_NAME})
pico_add_extra_outputs(${EXAMPLE_NAME})

target_sources(${EXAMPLE_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/main.c
)

target_link_libraries(${EXAMPLE_NAME}
  pico_stdlib
  ${DRV_NAME}
)