#include <stdlib.h>

#include "japariradio/page_master.hpp"
#include "lib/M24C64.hpp"
#include "lib/RDA5807M.h"
#include "lib/button.hpp"
#include "lib/c_font.h"
#include "lib/c_image.h"
#include "lib/settings.hpp"
#include "lib/ssd1306.h"
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

  settings.prepare();

  radio.begin(RDA5807M_BAND_WORLD);
  HAL_Delay(50);
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
