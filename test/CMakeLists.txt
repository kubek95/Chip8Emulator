cmake_minimum_required(VERSION 3.2)
project(emulator_tests)

add_subdirectory(lib/googletest)

include_directories(${EMULATOR_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/tests.cpp)

add_executable(emulator_tests ${SOURCE_FILES})
target_link_libraries(emulator_tests hardware gtest)
install(TARGETS emulator_tests DESTINATION bin)
