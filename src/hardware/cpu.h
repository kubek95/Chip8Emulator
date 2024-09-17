#ifndef SRC_HARDWARE_CPU_H
#define SRC_HARDWARE_CPU_H

#include <cstdint>
#include <array>

struct Cpu
{
    std::uint16_t program_counter;
    std::uint16_t index_register;
    std::uint8_t delay_timer;
    std::uint8_t sound_timer;
    std::array<std::uint8_t, 16> registers;
};

#endif