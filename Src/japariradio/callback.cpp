#include "japariradio/page_master.hpp"
#include "lib/button.hpp"
#include "main.h"

#if defined(STM32F303x8)
extern TIM_HandleTypeDef htim6;
#elif defined(STM32G031xx)
extern TIM_HandleTypeDef htim16;
#endif

extern PageMaster pageMaster;
extern Button buttonA;
extern Button buttonB;

// volatile uint32_t button0_tick       = 0;
// volatile uint32_t button1_tick       = 0;
// volatile GPIO_PinState button0_state = GPIO_PIN_SET;
// volatile GPIO_PinState button1_state = GPIO_PIN_SET;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  // Nothing to do
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  uint32_t tick       = HAL_GetTick();
  GPIO_PinState state = HAL_GPIO_ReadPin(GPIO_Pin == BUTTON0_Pin ? BUTTON0_GPIO_Port : BUTTON1_GPIO_Port, GPIO_Pin);

  if (GPIO_Pin == BUTTON0_Pin) {
    buttonA.update(tick, !state);

    // if (tick - button0_tick >= 50) {
    //   if (!state) {
    //     if (tick - button0_tick >= 1000)
    //       pageMaster.longPressAButton();
    //     else
    //       pageMaster.pressAButton();
    //   }

    //   button0_state = state;
    // }

    // button0_tick = tick;
  }

  if (GPIO_Pin == BUTTON1_Pin) {
    buttonB.update(tick, !state);

    // if (tick - button1_tick >= 50) {
    //   if (!state) {
    //     if (tick - button1_tick >= 1000)
    //       pageMaster.longPressBButton();
    //     else
    //       pageMaster.pressBButton();
    //   }

    //   button1_state = state;
    // }

    // button1_tick = tick;
  }
}

#if defined(STM32G031xx)
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
  HAL_GPIO_EXTI_Callback(GPIO_Pin);
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
  HAL_GPIO_EXTI_Callback(GPIO_Pin);
}
#endif
