cmake_minimum_required(VERSION 3.2)
project(emulator)

add_subdirectory(hardware)
set(SOURCE_FILES main.cpp)

add_executable(emulator_imp ${SOURCE_FILES})
target_link_libraries(emulator_imp hardware)
target_link_libraries(emulator_imp ${SDL2_LIBRARIES})
install(TARGETS emulator_imp DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
