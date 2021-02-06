#ifndef __M24C64_H
#define __M24C64_H

#include <stdint.h>

#if defined(STM32F303x8)
#include "stm32f3xx_hal.h"
#elif defined(STM32G031xx)
#include "stm32g0xx_hal.h"
#endif

template <uint8_t I2CADDRESS, uint32_t EEPLENGTH, uint8_t ADDRESSMODE, uint8_t PAGELENGTH>
class EEPHandler {
 private:
  I2C_HandleTypeDef *device;

  // Read/write mode
  enum ACCESSMODE { WRITEMODE, READMODE };

  // onWaiting Callback nullptr
  void (*onwaiting)() = 0;

  // checks if module is busy at the address
  bool busy(uint16_t address) {
    uint16_t i2c_address = I2CADDRESS;
    uint8_t dummy;

    return (HAL_I2C_Master_Transmit(this->device, i2c_address << 1, &dummy, 0, 5000) != HAL_OK);

    // EEP_WIRE.beginTransmission(i2c_address);
    // return (bool)EEP_WIRE.endTransmission();
  }

  // active waiting, computing time is given away
  void wait(uint16_t address) {
    while (busy(address))
      if (onwaiting) {
        onwaiting();  // Callback invoke
      }
  }

  // read a page
  void pageRead(uint16_t address, uint8_t *start, uint16_t length) {
    uint8_t buffer[2]    = { (uint8_t)(address >> 8), (uint8_t)(address & 0x00ff) };
    uint16_t i2c_address = I2CADDRESS;

    // address overrun
    if (address + length >= EEPLENGTH)
      return;

    wait(address);

    HAL_I2C_Master_Transmit(this->device, i2c_address << 1, buffer, 2, 5000);
    HAL_I2C_Master_Receive(this->device, i2c_address << 1, start, length, 5000);

    // EEP_WIRE.beginTransmission(i2c_address);
    // EEP_WIRE.write(highaddr);
    // EEP_WIRE.write(lowaddr);
    // EEP_WIRE.endTransmission();
    // EEP_WIRE.requestFrom(i2c_address, length);
    // while (EEP_WIRE.available()) *start++ = EEP_WIRE.read();
  }

  // writing a page
  void pageWrite(uint16_t address, uint8_t *start, uint16_t length) {
    if (address + length >= EEPLENGTH)
      return;

    uint16_t i2c_address = I2CADDRESS;
    uint8_t *buffer      = new uint8_t[length + 2];

    buffer[0] = (uint8_t)(address >> 8);
    buffer[1] = (uint8_t)(address & 0x00ff);

    for (uint16_t i = 2; i < length + 2; i++) buffer[i] = *start++;

    wait(address);

    HAL_I2C_Master_Transmit(this->device, i2c_address << 1, buffer, length + 2, 5000);

    // EEP_WIRE.beginTransmission(i2c_address);
    // EEP_WIRE.write(highaddr);
    // EEP_WIRE.write(lowaddr);

    // EEP_WIRE.endTransmission();

    delete[] buffer;
  }

  // Split a block access in pages
  template <ACCESSMODE MODE>
  void fastBlock(uint16_t address, void *start, uint16_t length) {
    uint16_t toReadWrite = length;
    uint8_t *ptr         = (uint8_t *)start;
    uint16_t addresse    = address;

    while (toReadWrite > 0) {
      uint16_t pageoffset = addresse % PAGELENGTH;
      uint16_t count      = PAGELENGTH - pageoffset;

      if (count > toReadWrite)
        count = toReadWrite;

      switch (MODE) {
        case READMODE: {
          pageRead(addresse, ptr, count);
          break;
        }

        case WRITEMODE: {
          pageWrite(addresse, ptr, count);
          break;
        }
      }

      ptr += count;
      toReadWrite -= count;
      addresse += count;
    }
  }

 public:
  EEPHandler(I2C_HandleTypeDef *device) {
    this->device = device;
  }

  // Block writing using the max. pagelen
  void fastBlockWrite(uint16_t address, void *start, uint16_t length) {
    fastBlock<WRITEMODE>(address, start, length);
  }

  // Block reading using the max. pagelen
  void fastBlockRead(uint16_t address, void *start, uint16_t length) {
    fastBlock<READMODE>(address, start, length);
  }

  // Module Ready?
  bool ready() {
    return !busy(I2CADDRESS);
  }

  // size of the eeprom in byte
  unsigned long length() {
    return EEPLENGTH;
  }

  // write single byte
  void write(uint16_t address, uint8_t value) {
    pageWrite(address, &value, 1);
  }

  // read single byte
  uint8_t read(uint16_t address) {
    uint8_t result = 0;
    pageRead(address, &result, 1);

    return result;
  }

  // Write byte if not equal to existing
  void update(uint16_t address, uint8_t value) {
    uint8_t old = read(address);

    if (old != value)
      write(address, value);
  }

  // read any data types
  void get(uint16_t address, uint8_t *ptr, uint16_t size) {
    // uint8_t *ptr = (uint8_t *)&customvar;

    for (size_t i = 0; i < size; i++) *ptr++ = read(address + i);
  }

  // write any data types
  void put(uint16_t address, uint8_t *ptr, uint16_t size) {
    // uint8_t *ptr = (uint8_t *)&customvar;

    for (uint16_t i = 0; i < size; i++) update(address + i, *ptr++);
  }

  // save callback
  void onWaiting(void (*callback)()) {
    onwaiting = callback;
  }
};

template <uint8_t I2CADDRESS = 0x50>
class M24C64 : public EEPHandler<I2CADDRESS, 8192UL, 2, 32> {
 public:
  M24C64(I2C_HandleTypeDef *device) : EEPHandler<I2CADDRESS, 8192UL, 2, 32>(device) {}
};

#endif
