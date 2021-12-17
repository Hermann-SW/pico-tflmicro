
cmake_minimum_required(VERSION 3.12)

project(display_imu C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(display_imu "")

target_include_directories(display_imu
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  display_imu
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(display_imu
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(
  display_imu
  pico_stdlib
  LCD_st7735
  ICM42622
  ICM20948
)

# enable usb output, disable uart output
pico_enable_stdio_usb(display_imu 1)
pico_enable_stdio_uart(display_imu 0)

pico_add_extra_outputs(display_imu)
