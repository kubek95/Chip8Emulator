#include "memory.h"

void Memory::writeRomToMemory(const std::vector<std::uint8_t>& content)
{
    std::copy(content.begin(), content.end(), main_memory_.begin() + userland_offset_);
}

std::uint8_t Memory::getByte(std::uint16_t memory_location) const
{
    return main_memory_[memory_location];
}