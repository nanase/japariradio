#include "lib/c_image.h"

static const uint8_t image_blank_data[5] = {
  0xf0, 0xf0, 0xf0, 0xf0, 0x40,
};
const CImage image_blank = { 5, 8, image_blank_data };
