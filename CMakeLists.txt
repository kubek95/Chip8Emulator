cmake_minimum_required(VERSION 3.2)

project(Chip8Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(EMULATOR_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(EMULATOR_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EMULATOR_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(EMULATOR_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/hardware)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${EMULATOR_INSTALL_INCLUDE_DIR})
include_directories(${EMULATOR_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)
