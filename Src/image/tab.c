#include "lib/c_image.h"

static const uint8_t image_tab_data[1] = {
  0x06,
};
const CImage image_tab = { 1, 2, image_tab_data };
