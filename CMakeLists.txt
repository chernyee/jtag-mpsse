cmake_minimum_required(VERSION 3.10)

project(jtagmpsse C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

if(NOT LIBUSB_FOUND)
    message(FATAL_ERROR "libusb-1.0 not found. Please install it (e.g., `sudo apt install libusb-1.0-0-dev`)")
endif()

set(LIB_SOURCES "jtag-mpsse.c")

add_library(jtagmpsse STATIC ${LIB_SOURCES})
set_target_properties(jtagmpsse PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(jtagmpsse PRIVATE ${LIBUSB})

# Optionally, specify public headers
target_include_directories(jtagmpsse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
