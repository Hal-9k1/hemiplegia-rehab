cmake_minimum_required(VERSION 3.13)

include(../pico-sdk/pico_sdk_init.cmake)

project(controller C CXX ASM)
pico_sdk_init()

if (NOT TARGET tinyusb_device)
  message(FATAL_ERROR "picosdk's TinyUSB submodule is required for serial output to USB.")
endif()

add_executable(controller
  main.cpp
  Vec3f.cpp
  IMU.cpp
  Motor.cpp
  )

pico_generate_pio_header(controller ${CMAKE_CURRENT_LIST_DIR}/motorSpeed.pio)

target_compile_features(controller PUBLIC
  cxx_std_17)

target_link_libraries(controller PUBLIC
  pico_stdlib
  hardware_i2c
  hardware_pio
  hardware_sync
  pico_time
  )
# output via USB, not UART
pico_enable_stdio_uart(controller 0)
pico_enable_stdio_usb(controller 1)

pico_add_extra_outputs(controller) # create uf2 and other stuff I don't care about
