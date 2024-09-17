#include "memory.h"

namespace emu {
Ram::Ram() : memory_{std::make_unique<char[]>(4096)} {}

void Ram::write(unsigned short address, char value) {
  memory_[address] = value;
}

char Ram::read(unsigned short address) const {
  return memory_[address];
}

}  // namespace emu