#ifndef SRC_HARDWARE_CPU_H
#define SRC_HARDWARE_CPU_H

namespace emu {
struct Cpu {
  short program_counter;
  short index_register;
  char delay_timer;
  char sound_timer;
  char V0;
  char V1;
  char V2;
  char V3;
  char V4;
  char V5;
  char V6;
  char V7;
  char V8;
  char V9;
  char VA;
  char VB;
  char VC;
  char VD;
  char VE;
  char VF;
};
}  // namespace emu

#endif