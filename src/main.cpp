#include "hardware/display.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

struct Cpu
{
    unsigned short program_counter;
    unsigned short index_register;
    unsigned char delay_timer;
    unsigned char sound_timer;
    std::array<unsigned char, 16> registers;
};

class Memory
{
  public:
    void writeRomToMemory(const std::vector<unsigned char>& content)
    {
        std::copy(content.begin(), content.end(), main_memory_.begin() + 512);
    }
    unsigned char getByte(unsigned short memory_location) const { return main_memory_[memory_location]; }

  private:
    std::array<unsigned char, 4092> main_memory_{};
};

unsigned short fetchInstruction(Cpu& cpu, const Memory& memory)
{
    unsigned short first_byte = memory.getByte(cpu.program_counter++);
    unsigned short second_byte = memory.getByte(cpu.program_counter++);
    return ((first_byte << 8) | second_byte);
}

auto readRom(std::string_view file_path)
{
    std::ifstream input(file_path.data(), std::ios::binary);
    return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
}

template <typename T>
std::string int_to_hex(T i)
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
    return stream.str();
}

std::uint8_t get_first_nibble(std::uint16_t opcode)
{
    return opcode >> 12;
}

std::uint8_t get_second_nibble(std::uint16_t opcode)
{
    return (opcode & 0x0F00) >> 8;
}

std::uint8_t get_third_nibble(std::uint16_t opcode)
{
    return (opcode & 0x00F0) >> 4;
}

std::uint8_t get_fourth_nibble(std::uint16_t opcode)
{
    return opcode & 0x000F;
}

int main()
{
    Memory ram;
    Cpu cpu;
    emu::Display display;
    cpu.program_counter = 512;
    ram.writeRomToMemory(readRom("test/lib/chip8-test-suite/bin/1-chip8-logo.ch8"));
    for (int i{0}; i < 61; ++i) {
        const auto opcode = fetchInstruction(cpu, ram);
        const auto first_nibble = get_first_nibble(opcode);
        switch (first_nibble) {
            case 0:
                display.clear_screen();
                break;
            case 1: {
                const unsigned short address = opcode & 0x0FFF;
                cpu.program_counter = address;
                std::cout << "jump to " << int_to_hex(address) << std::endl;
            } break;
            case 6: {
                const std::uint8_t reg = get_second_nibble(opcode);
                const std::uint16_t value = opcode & 0x00FF;
                cpu.registers.at(reg) = value;
                std::cout << "set register V" << static_cast<int>(reg) << " to " << value << std::endl;
            } break;
            case 7: {
                const std::uint8_t reg = get_second_nibble(opcode);
                const std::uint16_t value = opcode & 0x00FF;
                cpu.registers.at(reg) += value;
                std::cout << "add " << value << " to register V" << static_cast<int>(reg) << std::endl;
            } break;
            case 0xA: {
                const std::uint16_t value = opcode & 0x0FFF;
                cpu.index_register = value;
                std::cout << "set index register to " << value << std::endl;
            } break;
            case 0xD: {
                const std::uint8_t pos_x = cpu.registers.at(get_second_nibble(opcode));
                const std::uint8_t pos_y = cpu.registers.at(get_third_nibble(opcode));
                const std::uint8_t height = get_fourth_nibble(opcode);
                cpu.registers[0xF] = 0;
                for (int line{0}; line < height; ++line) {
                    const auto address = cpu.index_register + line;
                    const std::bitset<8> sprite = ram.getByte(address);
                    std::cout << address << std::endl;
                    std::cout << sprite << std::endl;
                    for (int bit{7}; bit >= 0; --bit) {
                        if (sprite.test(bit)) {
                            auto pixel_was_turned_off = display.toggle_pixel(pos_x + 7 - bit, pos_y + line);
                            if (pixel_was_turned_off) {
                                cpu.registers[0xF] = 1;
                            }
                        }
                    }
                }
                // std::puts("enter");
                // int x;
                // std::cin >> x;
                display.draw();
                std::cout << "draw sprite at (" << static_cast<int>(pos_x) << ", " << static_cast<int>(pos_y)
                          << ") height " << static_cast<int>(height) << std::endl;
            }
        }
    }

    while (true) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            return 0;
        }
    }
}
