#include "lib/settings.hpp"

#define EEP_HEADER_ADDRESS 0x00
#define EEP_MAGIC_NUMBER 0x42
#define EEP_DATA_LENGTH 8
#define EEP_MAX_BLOCK 1024

#define EEP_DEFAULT_FREQ 8000

/*
  Header
  Offset | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
  Value  | M | V |    Zero (Reserved)    |

  Data
  Offset | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
  Value  | M | V | Freq  |Zero (Reserved)|
*/

Settings::Settings(M24C64<> *eep) {
  this->eep     = eep;
  this->block   = 0;
  this->version = 0;
}

void Settings::prepareHeader(uint8_t *buffer) {
  this->eep->get(EEP_HEADER_ADDRESS, buffer, EEP_DATA_LENGTH);

  if (buffer[0] != EEP_MAGIC_NUMBER || *(uint16_t *)(buffer + 2) != 0x0000 || *(uint32_t *)(buffer + 4) != 0x00000000) {
    buffer[0]                 = EEP_MAGIC_NUMBER;
    buffer[1]                 = 0x00;  // version
    *(uint16_t *)(buffer + 2) = 0x0000;
    *(uint32_t *)(buffer + 4) = 0x00000000;

    this->eep->put(EEP_HEADER_ADDRESS, buffer, EEP_DATA_LENGTH);
    HAL_Delay(5);
  }
}

void Settings::prepare() {
  uint8_t buffer[EEP_DATA_LENGTH] = { 0 };

  if (!this->eep->ready()) {
    return;
  }

  this->prepareHeader(buffer);
  this->eep->get(EEP_HEADER_ADDRESS, buffer, EEP_DATA_LENGTH);

  this->version = buffer[1];

  for (this->block = 1; this->block < EEP_MAX_BLOCK; this->block++) {
    this->eep->get(this->block * EEP_DATA_LENGTH, buffer, EEP_DATA_LENGTH);

    if (buffer[0] != EEP_MAGIC_NUMBER || buffer[1] != this->version || *(uint32_t *)(buffer + 4) != 0x00000000) {
      break;
    }
  }

  if (--this->block == 0) {
    this->block               = 1;
    buffer[0]                 = EEP_MAGIC_NUMBER;
    buffer[1]                 = 0x00;        // version
    *(uint16_t *)(buffer + 2) = 8000;        // freq
    *(uint32_t *)(buffer + 4) = 0x00000000;  // reserved

    this->eep->put(this->block * EEP_DATA_LENGTH, buffer, EEP_DATA_LENGTH);
    HAL_Delay(5);
  }
}

void Settings::setValue(uint16_t freq) {
  uint8_t buffer[EEP_DATA_LENGTH] = { 0 };

  if (this->block == 0 || !this->eep->ready()) {
    return;
  }

  if (this->block >= EEP_MAX_BLOCK - 1) {
    this->version++;
    this->block = 0;

    buffer[0]                 = EEP_MAGIC_NUMBER;
    buffer[1]                 = this->version;
    *(uint16_t *)(buffer + 2) = 0x0000;
    *(uint32_t *)(buffer + 4) = 0x00000000;

    this->eep->put(EEP_HEADER_ADDRESS, buffer, EEP_DATA_LENGTH);
    HAL_Delay(5);
  }

  this->block++;
  buffer[0]                 = EEP_MAGIC_NUMBER;
  buffer[1]                 = this->version;  // version
  *(uint16_t *)(buffer + 2) = freq;           // freq
  *(uint32_t *)(buffer + 4) = 0x00000000;     // reserved

  this->eep->put(this->block * EEP_DATA_LENGTH, buffer, EEP_DATA_LENGTH);
  HAL_Delay(5);
}

uint16_t Settings::getValue() {
  uint8_t buffer[EEP_DATA_LENGTH] = { 0 };

  if (this->block == 0 || !this->eep->ready()) {
    return EEP_DEFAULT_FREQ;
  }

  this->eep->get(this->block * EEP_DATA_LENGTH, buffer, EEP_DATA_LENGTH);

  return *(uint16_t *)(buffer + 2);
}
