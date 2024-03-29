#include "lib/c_image.hpp"

#include "lib/ssd1306.hpp"

extern SSD1306_t SSD1306;

void cImage_write(const CImage *image) {
  uint8_t b_count = 0;
  uint8_t w_count = 0;
  uint8_t x_cur   = 0;
  uint8_t y_cur   = 0;

  for (uint16_t i = 0; i < image->size; i++) {
    b_count = image->data[i] >> 4;
    w_count = image->data[i] & 0x0f;

    for (uint8_t j = 0; j < b_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_black);
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }
    }

    for (uint8_t j = 0; j < w_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_white);
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }
    }
  }
}

void cImage_writeCropX(const CImage *image, uint8_t width) {
  uint8_t b_count = 0;
  uint8_t w_count = 0;
  uint8_t x_cur   = 0;
  uint8_t y_cur   = 0;

  for (uint16_t i = 0; i < image->size; i++) {
    b_count = image->data[i] >> 4;
    w_count = image->data[i] & 0x0f;

    for (uint8_t j = 0; j < b_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_black);
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }
    }

    for (uint8_t j = 0; j < w_count; j++) {
      if (x_cur < width)
        ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_white);
      else
        ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_black);

      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }
    }
  }
}

void cImage_writeCropY(const CImage *image, uint8_t height) {
  uint8_t b_count = 0;
  uint8_t w_count = 0;
  uint8_t x_cur   = 0;
  uint8_t y_cur   = 0;

  for (uint16_t i = 0; i < image->size; i++) {
    b_count = image->data[i] >> 4;
    w_count = image->data[i] & 0x0f;

    for (uint8_t j = 0; j < b_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_black);
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }

      if (y_cur >= height) {
        return;
      }
    }

    for (uint8_t j = 0; j < w_count; j++) {
      ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_white);
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }

      if (y_cur >= height) {
        return;
      }
    }
  }
}

void cImage_writeSlideY(const CImage *image, uint8_t slide) {
  uint8_t b_count = 0;
  uint8_t w_count = 0;
  uint8_t x_cur   = 0;
  uint8_t y_cur   = 0;

  for (uint16_t i = 0; i < image->size; i++) {
    b_count = image->data[i] >> 4;
    w_count = image->data[i] & 0x0f;

    for (uint8_t j = 0; j < b_count; j++) {
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }
    }

    for (uint8_t j = 0; j < w_count; j++) {
      if (y_cur < slide) {
        ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_black);
      } else {
        ssd1306_drawPixel(SSD1306.currentX + x_cur, SSD1306.currentY + y_cur, ssd1306_white);
      }
      x_cur++;

      if (x_cur >= image->width) {
        x_cur = 0;
        y_cur++;
      }
    }
  }
}
