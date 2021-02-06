#ifndef __CONFIG_H
#define __CONFIG_H

/* Buttons ------------------------------ */

// Lレベルが維持する最小時間(ms)
#define BUTTON_MIN_LOW_TIME 50

// Hレベルが維持する最小時間(ms)
#define BUTTON_MIN_HIGH_TIME 25

// 長押しと判定される時間(ms)
#define BUTTON_LONG_LOW_TIME 750

/* Display Contrast---------------------- */

// 最高輝度 (0-255)
#define CONTRAST_MAX 120

// 最低輝度 (0-255)
#define CONTRAST_MIN 10

// フェード開始遅延時間 (unit: 100ms, max: 25500ms)
#define FADE_DELAY 150

// フェード時の輝度減少量 (0-255)
#define FADE_DECREMENT 5

/* Display Contrast---------------------- */

// 最高輝度 (0-255)
#define CONTRAST_MAX 120

// 最低輝度 (0-255)
#define CONTRAST_MIN 10

/* Setting Contrast---------------------- */

// フェード開始遅延時間 (unit: 100ms, max: 25500ms)
#define SETTING_DELAY 100

#endif
