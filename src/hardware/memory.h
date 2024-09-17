#ifndef SRC_HARDWARE_MEMORY_H
#define SRC_HARDWARE_MEMORY_H

#include <array>
#include <cstdint>
#include <vector>

class Memory
{
  public:
    Memory() = default;
    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;

    void writeRomToMemory(const std::vector<std::uint8_t>& content);
    std::uint8_t getByte(std::uint16_t memory_location) const;

  private:
    static constexpr std::uint16_t memory_pool_{4092};
    static constexpr std::uint16_t userland_offset_{512};
    std::array<std::uint8_t, memory_pool_> main_memory_{};
};

#endif  // SRC_HARDWARE_MEMORY_H