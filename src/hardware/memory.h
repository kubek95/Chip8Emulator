#ifndef SRC_HARDWARE_MEMORY_H
#define SRC_HARDWARE_MEMORY_H

#include <memory>

namespace emu {
class Ram {
 public:
  Ram();
  void write(unsigned short address, char value);
  char read(unsigned short address) const; 

 private:
  std::unique_ptr<char[]> memory_;
};

class Stack {};
}  // namespace emu

#endif