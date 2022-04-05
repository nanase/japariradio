#include "lib/c_font.hpp"
#include "stdint.h"

static const uint8_t glyph_7x10_data_32[]  = { 0xf0, 0xf0, 0xf0, 0xf0, 0xa0 };
static const uint8_t glyph_7x10_data_37[]  = { 0x21, 0x51, 0x11, 0x11, 0x21, 0x12, 0x42, 0x51, 0x11,
                                              0x31, 0x11, 0x11, 0x41, 0x11, 0x51, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_44[]  = { 0xf0, 0xf0, 0xf0, 0x71, 0x61, 0x61, 0x30 };
static const uint8_t glyph_7x10_data_46[]  = { 0xf0, 0xf0, 0xf0, 0x71, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_47[]  = { 0x41, 0x61, 0x51, 0x61, 0x61, 0x61, 0x51, 0x61, 0xf0, 0x30 };
static const uint8_t glyph_7x10_data_48[]  = { 0x23, 0x31, 0x31, 0x21, 0x31, 0x21, 0x11, 0x11, 0x21,
                                              0x31, 0x21, 0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_49[]  = { 0x31, 0x52, 0x41, 0x11, 0x61, 0x61, 0x61, 0x61, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_50[]  = { 0x23, 0x31, 0x31, 0x21, 0x31, 0x61, 0x51, 0x51, 0x51, 0x55, 0xf0 };
static const uint8_t glyph_7x10_data_51[]  = { 0x23, 0x31, 0x31, 0x61, 0x42, 0x71, 0x61, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_52[]  = { 0x41, 0x52, 0x41, 0x11, 0x41, 0x11, 0x31,
                                              0x21, 0x35, 0x51, 0x61, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_53[]  = { 0x15, 0x21, 0x61, 0x64, 0x71, 0x61, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_54[]  = { 0x23, 0x31, 0x31, 0x21, 0x64, 0x31, 0x31,
                                              0x21, 0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_55[]  = { 0x15, 0x61, 0x51, 0x51, 0x61, 0x51, 0x61, 0x61, 0xf0, 0x30 };
static const uint8_t glyph_7x10_data_56[]  = { 0x23, 0x31, 0x31, 0x21, 0x31, 0x33, 0x31, 0x31,
                                              0x21, 0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_57[]  = { 0x23, 0x31, 0x31, 0x21, 0x31, 0x21, 0x31,
                                              0x34, 0x61, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_58[]  = { 0xf0, 0x21, 0xf0, 0xf0, 0x41, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_65[]  = { 0x31, 0x51, 0x11, 0x41, 0x11, 0x41, 0x11, 0x41,
                                              0x11, 0x35, 0x21, 0x31, 0x21, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_66[]  = { 0x14, 0x31, 0x31, 0x21, 0x31, 0x24, 0x31, 0x31,
                                              0x21, 0x31, 0x21, 0x31, 0x24, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_67[]  = { 0x23, 0x31, 0x31, 0x21, 0x61, 0x61, 0x61, 0x61, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_68[]  = { 0x13, 0x41, 0x21, 0x31, 0x31, 0x21, 0x31, 0x21,
                                              0x31, 0x21, 0x31, 0x21, 0x21, 0x33, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_69[]  = { 0x15, 0x21, 0x61, 0x65, 0x21, 0x61, 0x61, 0x65, 0xf0 };
static const uint8_t glyph_7x10_data_70[]  = { 0x15, 0x21, 0x61, 0x64, 0x31, 0x61, 0x61, 0x61, 0xf0, 0x40 };
static const uint8_t glyph_7x10_data_71[]  = { 0x23, 0x31, 0x31, 0x21, 0x61, 0x61, 0x13,
                                              0x21, 0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_72[]  = { 0x11, 0x31, 0x21, 0x31, 0x21, 0x31, 0x25, 0x21,
                                              0x31, 0x21, 0x31, 0x21, 0x31, 0x21, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_73[]  = { 0x23, 0x51, 0x61, 0x61, 0x61, 0x61, 0x61, 0x53, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_74[]  = { 0x51, 0x61, 0x61, 0x61, 0x61, 0x61, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_75[]  = { 0x11, 0x31, 0x21, 0x21, 0x31, 0x11, 0x42, 0x51,
                                              0x11, 0x41, 0x21, 0x31, 0x21, 0x31, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_76[]  = { 0x11, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x65, 0xf0 };
static const uint8_t glyph_7x10_data_77[]  = { 0x11, 0x31, 0x22, 0x12, 0x22, 0x12, 0x21, 0x11, 0x11,
                                              0x21, 0x31, 0x21, 0x31, 0x21, 0x31, 0x21, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_78[]  = { 0x11, 0x31, 0x22, 0x21, 0x22, 0x21, 0x21, 0x11, 0x11, 0x21,
                                              0x11, 0x11, 0x21, 0x22, 0x21, 0x22, 0x21, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_79[]  = { 0x23, 0x31, 0x31, 0x21, 0x31, 0x21, 0x31, 0x21,
                                              0x31, 0x21, 0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_80[]  = { 0x14, 0x31, 0x31, 0x21, 0x31, 0x21, 0x31,
                                              0x24, 0x31, 0x61, 0x61, 0xf0, 0x40 };
static const uint8_t glyph_7x10_data_81[]  = { 0x23, 0x31, 0x31, 0x21, 0x31, 0x21, 0x31, 0x21, 0x31,
                                              0x21, 0x31, 0x21, 0x11, 0x11, 0x33, 0x71, 0x80 };
static const uint8_t glyph_7x10_data_82[]  = { 0x14, 0x31, 0x31, 0x21, 0x31, 0x21, 0x31, 0x24,
                                              0x31, 0x21, 0x31, 0x21, 0x31, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_83[]  = { 0x23, 0x31, 0x31, 0x21, 0x72, 0x71, 0x71, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_84[]  = { 0x15, 0x41, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_85[]  = { 0x11, 0x31, 0x21, 0x31, 0x21, 0x31, 0x21, 0x31, 0x21,
                                              0x31, 0x21, 0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_86[]  = { 0x11, 0x31, 0x21, 0x31, 0x21, 0x31, 0x31, 0x11,
                                              0x41, 0x11, 0x41, 0x11, 0x51, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_87[]  = { 0x11, 0x31, 0x21, 0x31, 0x21, 0x11, 0x11, 0x21, 0x11, 0x11, 0x21,
                                              0x11, 0x11, 0x22, 0x12, 0x31, 0x11, 0x41, 0x11, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_88[]  = { 0x11, 0x31, 0x31, 0x11, 0x41, 0x11, 0x51, 0x61,
                                              0x51, 0x11, 0x41, 0x11, 0x31, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_89[]  = { 0x11, 0x31, 0x21, 0x31, 0x31, 0x11, 0x41,
                                              0x11, 0x51, 0x61, 0x61, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_90[]  = { 0x15, 0x61, 0x51, 0x51, 0x61, 0x51, 0x51, 0x65, 0xf0 };
static const uint8_t glyph_7x10_data_97[]  = { 0xf0, 0x13, 0x31, 0x31, 0x34, 0x21, 0x31, 0x21, 0x22, 0x32, 0x11, 0xf0 };
static const uint8_t glyph_7x10_data_98[]  = { 0x11, 0x61, 0x61, 0x12, 0x32, 0x21, 0x21, 0x31,
                                              0x21, 0x31, 0x22, 0x21, 0x21, 0x12, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_99[]  = { 0xf0, 0x13, 0x31, 0x31, 0x21, 0x61, 0x61, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_100[] = { 0x51, 0x61, 0x32, 0x11, 0x21, 0x22, 0x21, 0x31,
                                               0x21, 0x31, 0x21, 0x22, 0x32, 0x11, 0xf0 };
static const uint8_t glyph_7x10_data_101[] = { 0xf0, 0x13, 0x31, 0x31, 0x25, 0x21, 0x61, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_102[] = { 0x42, 0x41, 0x45, 0x41, 0x61, 0x61, 0x61, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_103[] = { 0xf0, 0x12, 0x11, 0x21, 0x22, 0x21, 0x31, 0x21,
                                               0x31, 0x21, 0x22, 0x32, 0x11, 0x61, 0x24, 0x20 };
static const uint8_t glyph_7x10_data_104[] = { 0x11, 0x61, 0x61, 0x12, 0x32, 0x21, 0x21, 0x31,
                                               0x21, 0x31, 0x21, 0x31, 0x21, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_105[] = { 0x31, 0xb3, 0x61, 0x61, 0x61, 0x61, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_106[] = { 0x31, 0xb3, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x33, 0x40 };
static const uint8_t glyph_7x10_data_107[] = { 0x11, 0x61, 0x61, 0x21, 0x31, 0x11, 0x42,
                                               0x51, 0x11, 0x41, 0x21, 0x31, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_108[] = { 0x13, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_109[] = { 0xf4, 0x31, 0x11, 0x11, 0x21, 0x11, 0x11, 0x21, 0x11,
                                               0x11, 0x21, 0x11, 0x11, 0x21, 0x11, 0x11, 0xf0 };
static const uint8_t glyph_7x10_data_110[] = { 0xf1, 0x12, 0x32, 0x21, 0x21, 0x31, 0x21,
                                               0x31, 0x21, 0x31, 0x21, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_111[] = { 0xf0, 0x13, 0x31, 0x31, 0x21, 0x31, 0x21,
                                               0x31, 0x21, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_112[] = { 0xf1, 0x12, 0x32, 0x21, 0x21, 0x31, 0x21, 0x31,
                                               0x22, 0x21, 0x21, 0x12, 0x31, 0x61, 0x50 };
static const uint8_t glyph_7x10_data_113[] = { 0xf0, 0x12, 0x11, 0x21, 0x22, 0x21, 0x31, 0x21,
                                               0x31, 0x21, 0x22, 0x32, 0x11, 0x61, 0x61, 0x10 };
static const uint8_t glyph_7x10_data_114[] = { 0xf1, 0x12, 0x32, 0x21, 0x21, 0x61, 0x61, 0x61, 0xf0, 0x40 };
static const uint8_t glyph_7x10_data_115[] = { 0xf0, 0x13, 0x31, 0x31, 0x32, 0x71, 0x31, 0x31, 0x33, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_116[] = { 0x21, 0x61, 0x54, 0x41, 0x61, 0x61, 0x61, 0x72, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_117[] = { 0xf1, 0x31, 0x21, 0x31, 0x21, 0x31, 0x21,
                                               0x31, 0x21, 0x22, 0x32, 0x11, 0xf0 };
static const uint8_t glyph_7x10_data_118[] = { 0xf1, 0x31, 0x21, 0x31, 0x31, 0x11, 0x41,
                                               0x11, 0x41, 0x11, 0x51, 0xf0, 0x20 };
static const uint8_t glyph_7x10_data_119[] = { 0xf1, 0x11, 0x11, 0x21, 0x11, 0x11, 0x21, 0x11, 0x11,
                                               0x22, 0x12, 0x31, 0x11, 0x41, 0x11, 0xf0, 0x10 };
static const uint8_t glyph_7x10_data_120[] = { 0xf1, 0x31, 0x31, 0x11, 0x51, 0x61, 0x51, 0x11, 0x31, 0x31, 0xf0 };
static const uint8_t glyph_7x10_data_121[] = { 0xf1, 0x31, 0x21, 0x31, 0x31, 0x11, 0x41,
                                               0x11, 0x51, 0x61, 0x61, 0x42, 0x40 };
static const uint8_t glyph_7x10_data_122[] = { 0xf5, 0x51, 0x51, 0x51, 0x51, 0x65, 0xf0 };

static const CGlyph glyphs_7x10[] = {
  { ' ', 5, glyph_7x10_data_32 },
  // { '%', 17, glyph_7x10_data_37 },
  // { ',', 7, glyph_7x10_data_44 },
  // { '.', 6, glyph_7x10_data_46 },
  // { '/', 10, glyph_7x10_data_47 },
  // { '0', 17, glyph_7x10_data_48 },
  // { '1', 11, glyph_7x10_data_49 },
  // { '2', 11, glyph_7x10_data_50 },
  // { '3', 12, glyph_7x10_data_51 },
  // { '4', 13, glyph_7x10_data_52 },
  // { '5', 11, glyph_7x10_data_53 },
  // { '6', 14, glyph_7x10_data_54 },
  // { '7', 10, glyph_7x10_data_55 },
  // { '8', 15, glyph_7x10_data_56 },
  // { '9', 14, glyph_7x10_data_57 },
  // { ':', 7, glyph_7x10_data_58 },
  // { 'A', 15, glyph_7x10_data_65 },
  // { 'B', 15, glyph_7x10_data_66 },
  // { 'C', 12, glyph_7x10_data_67 },
  // { 'D', 16, glyph_7x10_data_68 },
  // { 'E', 9, glyph_7x10_data_69 },
  // { 'F', 10, glyph_7x10_data_70 },
  // { 'G', 14, glyph_7x10_data_71 },
  { 'H', 16, glyph_7x10_data_72 },
  // { 'I', 10, glyph_7x10_data_73 },
  // { 'J', 11, glyph_7x10_data_74 },
  // { 'K', 16, glyph_7x10_data_75 },
  // { 'L', 9, glyph_7x10_data_76 },
  { 'M', 18, glyph_7x10_data_77 },
  // { 'N', 19, glyph_7x10_data_78 },
  // { 'O', 16, glyph_7x10_data_79 },
  // { 'P', 13, glyph_7x10_data_80 },
  // { 'Q', 17, glyph_7x10_data_81 },
  // { 'R', 15, glyph_7x10_data_82 },
  // { 'S', 12, glyph_7x10_data_83 },
  // { 'T', 10, glyph_7x10_data_84 },
  // { 'U', 17, glyph_7x10_data_85 },
  // { 'V', 16, glyph_7x10_data_86 },
  // { 'W', 21, glyph_7x10_data_87 },
  // { 'X', 15, glyph_7x10_data_88 },
  // { 'Y', 14, glyph_7x10_data_89 },
  // { 'Z', 9, glyph_7x10_data_90 },
  // { 'a', 12, glyph_7x10_data_97 },
  // { 'b', 16, glyph_7x10_data_98 },
  // { 'c', 11, glyph_7x10_data_99 },
  // { 'd', 15, glyph_7x10_data_100 },
  // { 'e', 11, glyph_7x10_data_101 },
  // { 'f', 10, glyph_7x10_data_102 },
  // { 'g', 16, glyph_7x10_data_103 },
  // { 'h', 15, glyph_7x10_data_104 },
  // { 'i', 9, glyph_7x10_data_105 },
  // { 'j', 10, glyph_7x10_data_106 },
  // { 'k', 14, glyph_7x10_data_107 },
  // { 'l', 10, glyph_7x10_data_108 },
  // { 'm', 17, glyph_7x10_data_109 },
  // { 'n', 13, glyph_7x10_data_110 },
  // { 'o', 13, glyph_7x10_data_111 },
  // { 'p', 15, glyph_7x10_data_112 },
  // { 'q', 16, glyph_7x10_data_113 },
  // { 'r', 10, glyph_7x10_data_114 },
  // { 's', 11, glyph_7x10_data_115 },
  // { 't', 10, glyph_7x10_data_116 },
  // { 'u', 13, glyph_7x10_data_117 },
  // { 'v', 13, glyph_7x10_data_118 },
  // { 'w', 17, glyph_7x10_data_119 },
  // { 'x', 11, glyph_7x10_data_120 },
  // { 'y', 13, glyph_7x10_data_121 },
  { 'z', 7, glyph_7x10_data_122 },
};

const CFont font_7x10 = { 7, 10, 4, glyphs_7x10 };
