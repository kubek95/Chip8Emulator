#include "hardware/display.h"
#include "hardware/opcode_utils.h"
#include "hardware/memory.h"
#include "hardware/cpu.h"
#include <SDL2/SDL.h>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

std::uint16_t fetchInstruction(Cpu& cpu, const Memory& memory)
{
    std::uint16_t first_byte = memory.getByte(cpu.program_counter++);
    std::uint16_t second_byte = memory.getByte(cpu.program_counter++);
    return ((first_byte << 8) | second_byte);
}

auto readRom(std::string_view file_path)
{
    std::ifstream input(file_path.data(), std::ios::binary);
    return std::vector<std::uint8_t>(std::istreambuf_iterator<char>(input), {});
}

template <typename T>
std::string intToHex(T i)
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
    return stream.str();
}

int main()
{
    Memory ram;
    Cpu cpu;
    emu::Display display;
    std::stack<std::uint16_t> stack;
    cpu.program_counter = 512;
    ram.writeRomToMemory(readRom("test/lib/chip8-test-suite/bin/1-chip8-logo.ch8"));
    for (int i{0}; i < 61; ++i) {
        const auto opcode = fetchInstruction(cpu, ram);
        const auto first_nibble = getFirstNibble(opcode);
        switch (first_nibble) {
            case 0U: {
                const auto fourth_nibble = getFourthNibble(opcode);
                switch (fourth_nibble) {
                    case 0:
                        display.clear_screen();
                        break;
                    case 0xE: {
                        if (stack.empty()) {
                            std::abort();
                        }
                        cpu.program_counter = stack.top();
                        stack.pop();
                    } break;
                }
            } break;
            case 1U: {
                const auto address = getLastTwelveBits(opcode);
                cpu.program_counter = address;
                std::cout << "jump to " << intToHex(address) << std::endl;
            } break;
            case 2U: {
                stack.push(cpu.program_counter);
                cpu.program_counter = getLastTwelveBits(opcode);
            } break;
            case 3U: {
                const auto reg = getSecondNibble(opcode);
                const auto value = getSecondByte(opcode);
                if (cpu.registers[reg] == value) {
                    cpu.program_counter += 2;
                }
            } break;
            case 4U: {

            } break;
            case 5U: {

            }
            case 6U: {
                const auto reg = getSecondNibble(opcode);
                const auto value = getSecondByte(opcode);
                cpu.registers.at(reg) = value;
                std::cout << "set register V" << static_cast<int>(reg) << " to " << value << std::endl;
            } break;
            case 7U: {
                const auto reg = getSecondNibble(opcode);
                const auto value = getSecondByte(opcode);
                cpu.registers.at(reg) += value;
                std::cout << "add " << value << " to register V" << static_cast<int>(reg) << std::endl;
            } break;
            case 9U: {
                
            } break;
            case 0xAU: {
                const auto value = getLastTwelveBits(opcode);
                cpu.index_register = value;
                std::cout << "set index register to " << value << std::endl;
            } break;
            case 0xDU: {
                const std::uint8_t pos_x = cpu.registers.at(getSecondNibble(opcode));
                const std::uint8_t pos_y = cpu.registers.at(getThirdNibble(opcode));
                const std::uint8_t height = getFourthNibble(opcode);
                cpu.registers[0xF] = 0;
                for (int line{0}; line < height; ++line) {
                    const auto address = cpu.index_register + line;
                    const std::bitset<8> sprite = ram.getByte(address);
                    for (int bit{7}; bit >= 0; --bit) {
                        if (sprite.test(bit)) {
                            auto pixel_was_turned_off = display.toggle_pixel(pos_x + 7 - bit, pos_y + line);
                            if (pixel_was_turned_off) {
                                cpu.registers[0xF] = 1;
                            }
                        }
                    }
                }
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
