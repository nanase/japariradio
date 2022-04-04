#include <stdlib.h>

#include "japariradio/page_master.hpp"
#include "lib/M24C64.hpp"
#include "lib/RDA5807M.hpp"
#include "lib/button.hpp"
#include "lib/c_font.hpp"
#include "lib/c_image.hpp"
#include "lib/settings.hpp"
#include "lib/ssd1306.hpp"
#include "main.h"

#if defined(STM32F303x8)
M24C64<> eep(&hi2c1);
RDA5807M radio(&hi2c1);
extern TIM_HandleTypeDef htim6;
#elif defined(STM32G031xx)
M24C64<> eep(&hi2c2);
RDA5807M radio(&hi2c2);
extern TIM_HandleTypeDef htim16;
#endif

PageMaster pageMaster;
Button buttonA, buttonB;
char buf[32];
Settings settings(&eep);

extern const CImage image_radio;
extern const CImage image_rod;
extern const CImage image_slider;
extern const CImage image_tab;
extern const CImage image_title_japari;
extern const CImage image_title_radio;

void title() {
  // 1
  radio.begin(RDA5807M_BAND_WORLD);
  radio.setVolume(0);
  radio.setFrequency(settings.getValue());
  HAL_Delay(1000);

  {
    // title: Japari
    ssd1306_setFillMode(true);
    ssd1306_setCursor(40, 0);
    cImage_write(&image_title_japari);
    ssd1306_updateScreen();
  }

  // 2
  radio.begin(RDA5807M_BAND_WORLD);
  radio.setVolume(0);
  radio.setFrequency(settings.getValue());
  HAL_Delay(1000);

  {
    // title: Radio
    ssd1306_setFillMode(false);
    ssd1306_setCursor(64, 16);
    cImage_write(&image_title_radio);
    ssd1306_updateScreen();
  }

  // 3
  radio.begin(RDA5807M_BAND_WORLD);
  radio.setVolume(0);
  radio.setFrequency(settings.getValue());
  HAL_Delay(1000);

  // 4
  radio.begin(RDA5807M_BAND_WORLD);
  radio.setVolume(0);
  radio.setFrequency(settings.getValue());
  HAL_Delay(1000);

  // 5
  radio.begin(RDA5807M_BAND_WORLD);
  radio.setVolume(0);
  radio.setFrequency(settings.getValue());
  HAL_Delay(1000);
}

void setup() {
  ssd1306_initialize();
  ssd1306_setContrast(0x7f);
  ssd1306_fill(ssd1306_black);
  ssd1306_updateScreen();

#if defined(STM32F303x8)
  HAL_TIM_Base_Start_IT(&htim6);
#elif defined(STM32G031xx)
  HAL_TIM_Base_Start_IT(&htim16);
#endif

  {
    // radio
    ssd1306_setFillMode(true);
    ssd1306_setCursor(1, 13);
    cImage_write(&image_radio);

    // rod
    ssd1306_setCursor(8, 0);
    cImage_write(&image_rod);

    // slider & tab
    ssd1306_setFillMode(true);
    ssd1306_setCursor(4, 25);
    cImage_write(&image_slider);

    ssd1306_setFillMode(false);
    ssd1306_setCursor(4 + 9 - (8000 - 7600) / 352, 25);
    cImage_write(&image_tab);
    ssd1306_updateScreen();
  }

  settings.prepare();

  title();

  radio.setFrequency(settings.getValue());
  radio.setVolume(15);

  pageMaster.initialize();
}

void loop() {
  static uint8_t count = 0;
  uint32_t tick        = HAL_GetTick();

  if (buttonA.checkLongPressed(tick))
    pageMaster.longPressAButton();
  else if (buttonA.checkClicked())
    pageMaster.pressAButton();

  if (buttonB.checkLongPressed(tick))
    pageMaster.longPressBButton();
  else if (buttonB.checkClicked())
    pageMaster.pressBButton();

  if (++count > 100) {
    pageMaster.update();
  }

  HAL_Delay(1);
}
