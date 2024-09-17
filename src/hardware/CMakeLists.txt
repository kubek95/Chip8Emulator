cmake_minimum_required(VERSION 3.2)
project(hardware C CXX)

set(SOURCE_FILES
    cpu.cpp
    memory.cpp
    display.cpp
)

set(HEADER_FILES
    cpu.h
    memory.h
    display.h
    opcode_utils.h)

add_library(hardware SHARED STATIC ${SOURCE_FILES} ${HEADER_FILES})

install(TARGETS hardware DESTINATION ${EMULATOR_INSTALL_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${EMULATOR_INSTALL_INCLUDE_DIR})
