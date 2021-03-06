#ifndef __SSD1306_H
#define __SSD1306_H

#include <stdbool.h>

/**
 * This Library is written and optimized by Olivier Van den Eede(4ilo) in 2016
 * for Stm32 Uc and HAL-i2c lib's.
 *
 * To use this library with ssd1306 oled display you will need to customize the defines below.
 *
 * This library uses 2 extra files (fonts.c/h).
 * In this files are 3 different fonts you can use:
 *   - Font_7x10
 *   - Font_11x18
 *   - Font_16x26
 *
 */

#if defined(STM32F303x8)
#include "stm32f3xx_hal.h"
#elif defined(STM32G031xx)
#include "stm32g0xx_hal.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

// I2c port as defined in main generated by CubeMx
#if defined(STM32F303x8)
#define SSD1306_I2C_PORT hi2c1
#elif defined(STM32G031xx)
#define SSD1306_I2C_PORT hi2c2
#endif

// I2c address
#define SSD1306_I2C_ADDR 0x78
// SSD1306 width in pixels
#define SSD1306_WIDTH 128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT 32

/** Set Lower Column Start Address for Page Addressing Mode. */
#define SSD1306_SETLOWCOLUMN 0x00
/** Set Higher Column Start Address for Page Addressing Mode. */
#define SSD1306_SETHIGHCOLUMN 0x10
/** Set Memory Addressing Mode. */
#define SSD1306_MEMORYMODE 0x20
/** Set display RAM display start line register from 0 - 63. */
#define SSD1306_SETSTARTLINE 0x40
/** Set Display Contrast to one of 256 steps. */
#define SSD1306_SETCONTRAST 0x81
/** Enable or disable charge pump.  Follow with 0X14 enable, 0X10 disable. */
#define SSD1306_CHARGEPUMP 0x8D
/** Set Segment Re-map between data column and the segment driver. */
#define SSD1306_SEGREMAP 0xA0

/** Resume display from GRAM content. */
#define SSD1306_DISPLAYALLON_RESUME 0xA4
/** Force display on regardless of GRAM content. */
#define SSD1306_DISPLAYALLON 0xA5

/** Set Normal Display. */
#define SSD1306_NORMALDISPLAY 0xA6
/** Set Inverse Display. */
#define SSD1306_INVERTDISPLAY 0xA7
/** Set Multiplex Ratio from 16 to 63. */
#define SSD1306_SETMULTIPLEX 0xA8

/** Set Display off. */
#define SSD1306_DISPLAYOFF 0xAE
/** Set Display on. */
#define SSD1306_DISPLAYON 0xAF

/**Set GDDRAM Page Start Address. */
#define SSD1306_SETSTARTPAGE 0xB0
/** Set COM output scan direction normal. */
#define SSD1306_COMSCANINC 0xC0
/** Set COM output scan direction reversed. */
#define SSD1306_COMSCANDEC 0xC8
/** Set Display Offset. */
#define SSD1306_SETDISPLAYOFFSET 0xD3
/** Sets COM signals pin configuration to match the OLED panel layout. */
#define SSD1306_SETCOMPINS 0xDA
/** This command adjusts the VCOMH regulator output. */
#define SSD1306_SETVCOMDETECT 0xDB
/** Set Display Clock Divide Ratio/ Oscillator Frequency. */
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
/** Set Pre-charge Period */
#define SSD1306_SETPRECHARGE 0xD9
/** Deactivate scroll */
#define SSD1306_DEACTIVATE_SCROLL 0x2E
/** No Operation Command. */
#define SSD1306_NOP 0xE3

//
//  Enumeration for screen colors
//
typedef enum {
  ssd1306_black = 0x00,  // ssd1306_black color, no pixel
  ssd1306_white = 0x01   // Pixel is set. Color depends on LCD
} SSD1306_COLOR;

//
//  Struct to store transformations
//
typedef struct {
  uint16_t currentX;
  uint16_t currentY;
  bool fillMode;
} SSD1306_t;

//	Definition of the i2c port in main
extern I2C_HandleTypeDef SSD1306_I2C_PORT;

//
//  Function definitions
//
uint8_t ssd1306_initialize(void);

void ssd1306_updateScreen(void);
void ssd1306_fill(SSD1306_COLOR color);
void ssd1306_drawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
void ssd1306_setCursor(uint8_t x, uint8_t y);
void ssd1306_setFillMode(bool);

void ssd1306_setContrast(uint8_t contrast);
void ssd1306_displayOn();
void ssd1306_displayOff();

#ifdef __cplusplus
}
#endif

#endif
