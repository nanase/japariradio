#include "config/config.h"
#include "japariradio/page.hpp"
#include "lib/RDA5807M.h"
#include "lib/c_font.h"
#include "lib/c_image.h"
#include "lib/settings.hpp"
#include "lib/ssd1306.h"

extern char buf[32];
extern RDA5807M radio;
extern Settings settings;

extern const CImage image_radio;
extern const CImage image_rod;
extern const CImage image_slider;
extern const CImage image_tab;
extern const CImage image_strength;
extern const CImage image_stereo;
extern const CImage image_seek_up;
extern const CImage image_seek_down;
extern const CImage image_blank;

bool seekDirection = false;

void fading(uint16_t frequency);
void settingSaving(uint16_t frequency);
void updateImages(uint16_t frequency);

void TuningPage::drawWholeScreen() {
  ssd1306_setFillMode(true);
  ssd1306_setCursor(107, 21);
  cFont_writeString(&font_7x10, "MHz");

  ssd1306_setFillMode(false);
  ssd1306_setCursor(82, 16);
  cFont_writeString(&font_11x18, ".");

  // radio
  ssd1306_setFillMode(true);
  ssd1306_setCursor(1, 13);
  cImage_write(&image_radio);

  // rod
  ssd1306_setCursor(8, 0);
  cImage_write(&image_rod);
}

bool TuningPage::draw() {
  uint16_t frequency = radio.getFrequency();

  ssd1306_setFillMode(true);
  ssd1306_setCursor(89, 8);
  sprintf(buf, "%d", (frequency % 100) / 10);
  cFont_writeString(&font_16x26, buf);

  ssd1306_setCursor(36, 8);
  sprintf(buf, "%3d", frequency / 100);
  cFont_writeString(&font_16x26, buf);

  fading(frequency);
  updateImages(frequency);
  settingSaving(frequency);

  return false;
}

void updateImages(uint16_t frequency) {
  // slider & tab
  ssd1306_setFillMode(true);
  ssd1306_setCursor(4, 25);
  cImage_write(&image_slider);

  ssd1306_setFillMode(false);
  ssd1306_setCursor(4 + 9 - (frequency - 7600) / 352, 25);
  cImage_write(&image_tab);

  // strength
  uint8_t strength = radio.getRSSI();

  if (strength > 78)
    strength = 78;

  ssd1306_setFillMode(true);
  ssd1306_setCursor(16, 0);
  cImage_writeCropX(&image_strength, strength / 6);

  // rod
  ssd1306_setFillMode(false);
  ssd1306_setCursor(8, 0);
  cImage_write(&image_rod);

  // status
  uint16_t status = radio.getRegister(RDA5807M_REG_STATUS);
  ssd1306_setCursor(2, 1);
  ssd1306_setFillMode(true);

  if (!(status & RDA5807M_STATUS_STC)) {
    cImage_write(seekDirection ? &image_seek_up : &image_seek_down);
  } else if (status & RDA5807M_STATUS_ST) {
    cImage_write(&image_stereo);
  } else {
    cImage_write(&image_blank);
  }
}

void settingSaving(uint16_t frequency) {
  static uint16_t oldFrequency = 0;
  static uint8_t delayCount    = 0;

  // fade out contrast
  if (frequency != oldFrequency) {
    delayCount   = 0;
    oldFrequency = frequency;
  } else {
    if (delayCount < SETTING_DELAY) {
      delayCount++;

      if (delayCount == SETTING_DELAY) {
        settings.setValue(frequency);
      }
    }
  }
}

void fading(uint16_t frequency) {
  static uint16_t oldFrequency = 0;
  static uint8_t fadeCount     = 0;
  static uint8_t contrast      = CONTRAST_MAX;

  // fade out contrast
  if (frequency != oldFrequency) {
    fadeCount    = 0;
    oldFrequency = frequency;
    contrast     = CONTRAST_MAX;
    ssd1306_setContrast(contrast);
  } else {
    if (fadeCount < FADE_DELAY) {
      fadeCount++;
    } else {
      if (contrast > CONTRAST_MIN) {
        contrast -= FADE_DECREMENT;
        ssd1306_setContrast(contrast);
      }
    }
  }
}

bool TuningPage::onPressButtonA() {
  uint16_t frequency = radio.getFrequency() + 10;

  if (frequency > 10800)
    frequency = 7600;

  radio.setFrequency(frequency);
  seekDirection = true;
  return false;
}

bool TuningPage::onPressButtonB() {
  uint16_t frequency = radio.getFrequency() - 10;

  if (frequency < 7600)
    frequency = 10800;

  radio.setFrequency(frequency);
  seekDirection = false;
  return false;
}

bool TuningPage::onLongPressButtonA() {
  radio.seekUp();
  seekDirection = true;
  return false;
}

bool TuningPage::onLongPressButtonB() {
  radio.seekDown();
  seekDirection = false;
  return false;
}
