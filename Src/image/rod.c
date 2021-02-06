#include "lib/c_image.h"

static const uint8_t image_rod_data[22] = {
  0xc1, 0xc3, 0xa3, 0xa3, 0xa3, 0xa1, 0x11, 0xa1, 0x11, 0xa1, 0x11,
  0xa1, 0x11, 0xa1, 0x11, 0xa1, 0x11, 0xa1, 0x11, 0xa1, 0x11, 0xb0,
};
const CImage image_rod = { 22, 14, image_rod_data };
