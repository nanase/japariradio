#ifndef __SETTING_H
#define __SETTING_H

#include <stdint.h>

#include "lib/M24C64.hpp"

class Settings {
 public:
  Settings(M24C64<> *eep);

  void prepare();
  void setValue(uint16_t freq);
  uint16_t getValue();

 private:
  M24C64<> *eep;
  uint16_t block;
  uint8_t version;

  void prepareHeader(uint8_t *buffer);
};

#endif
