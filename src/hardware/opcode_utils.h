#ifndef SRC_HARDWARE_OPCODE_UTILS_H
#define SRC_HARDWARE_OPCODE_UTILS_H

#include <cstdint>

inline std::uint8_t getFirstNibble(std::uint16_t opcode) noexcept
{
    return opcode >> 12;
}

inline std::uint8_t getSecondNibble(std::uint16_t opcode) noexcept
{
    return (opcode & 0x0F00) >> 8;
}

inline std::uint8_t getThirdNibble(std::uint16_t opcode) noexcept
{
    return (opcode & 0x00F0) >> 4;
}

inline std::uint8_t getFourthNibble(std::uint16_t opcode) noexcept
{
    return opcode & 0x000F;
}

inline std::uint8_t getFirstByte(std::uint16_t opcode) noexcept
{
    return opcode >> 8;
}

inline std::uint8_t getSecondByte(std::uint16_t opcode) noexcept
{
    return opcode & 0x00FF;
}

inline std::uint16_t getLastTwelveBits(std::uint16_t opcode) noexcept
{
    return opcode & 0x0FFF;
}

#endif  // SRC_HARDWARE_OPCODE_UTILS_H