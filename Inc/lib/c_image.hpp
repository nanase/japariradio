#ifndef __C_IMAGE_H
#define __C_IMAGE_H

#include "stdint.h"

typedef struct {
  uint16_t size;
  uint8_t width;
  const uint8_t *data;
} CImage;

void cImage_write(const CImage *image);
void cImage_writeCropX(const CImage *image, uint8_t width);
void cImage_writeSlideY(const CImage *image, uint8_t slide);

#include "image_data.hpp"

#endif
