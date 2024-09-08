cmake_minimum_required(VERSION 3.2)
project(hardware C CXX)

set(SOURCE_FILES
    cpu.h
    cpu.cpp
)

add_library(hardware SHARED STATIC ${SOURCE_FILES})

install(TARGETS hardware DESTINATION ${EMULATOR_INSTALL_LIB_DIR})
install(FILES cpu.h DESTINATION ${EMULATOR_INSTALL_INCLUDE_DIR})
