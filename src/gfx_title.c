#include "wasm4.h"

// SPRITE_Title
const uint8_t SPRITE_Title[1536] = { 0x1b,0x00,0x00,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xaa,0xaa,0xaa,0xaa,0xc0,0x00,0x00,0x01,0x00,0x03,0xff,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xf0,0x00,0x00,0x05,0x00,0xff,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xfa,0x50,0x00,0x0a,0x0f,0xea,0xaa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe9,0x40,0x00,0x02,0x3e,0xaa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xa5,0x00,0x00,0x00,0xfa,0xbf,0xff,0x00,0x00,0x30,0x00,0x00,0xc0,0xff,0x0c,0x0c,0x94,0x00,0x00,0x00,0xea,0xf0,0x3f,0x03,0xfc,0x30,0x3f,0xff,0xc0,0xff,0x0c,0x0c,0x50,0x00,0x00,0x00,0xea,0xf0,0x3f,0x03,0xfc,0x30,0x3f,0xff,0xc0,0xff,0x0c,0x0c,0x40,0x00,0x00,0x00,0xea,0xf0,0x3f,0x00,0x00,0x30,0x3f,0xff,0xc0,0x00,0x0c,0x0c,0x00,0x00,0x00,0x00,0xfa,0xbf,0xff,0x03,0xfc,0x30,0x00,0x00,0xc0,0xff,0x0c,0x0c,0x00,0x00,0x00,0x00,0x3e,0xaa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x0f,0xea,0xaa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0xff,0xea,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xfe,0xaa,0xaa,0xaa,0xaa,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xaa,0xaa,0xaa,0xaa,0xaa,0xab,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xfa,0xa0,0x20,0x20,0x20,0x20,0x2a,0xbf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xaa,0xa2,0x22,0xa8,0xa2,0x22,0x2a,0xab,0xc0,0x00,0x00,0x00,0x00,0x00,0x0f,0xfe,0xaa,0xa2,0x20,0x28,0xa2,0x22,0x2a,0xaa,0xff,0x00,0x00,0x00,0x00,0x00,0xff,0xaf,0xaa,0xa0,0xa2,0xa8,0xa0,0xa2,0x2a,0xab,0xeb,0xff,0x00,0x00,0x00,0x00,0xaa,0xab,0xfa,0xa2,0x20,0x28,0xa2,0x20,0x2a,0xbf,0xaa,0xab,0xff,0x00,0x00,0x00,0xaa,0xaa,0xbf,0xea,0xaa,0xaa,0xaa,0xaa,0xaf,0xfa,0xaa,0xaa,0xab,0xff,0xff,0xff,0xaa,0xaa,0xaa,0xff,0xff,0xff,0xff,0xff,0xfe,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xab,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xf0,0x3f,0x03,0xc0,0x00,0x0c,0x00,0x00,0x00,0xf0,0x00,0x0c,0x00,0x00,0x3f,0xff,0xfc,0x3f,0x0f,0xc3,0xff,0xfc,0x3f,0x0f,0xc0,0xf0,0xff,0xfc,0x3f,0xc0,0x00,0x00,0xfc,0x0c,0x0f,0xc0,0x00,0x0c,0x3f,0x0f,0xc0,0xf0,0x00,0x0c,0x3f,0xc0,0x3f,0xff,0xff,0x00,0x3f,0xc3,0xff,0xfc,0x3f,0x0f,0xc0,0xf0,0xff,0xfc,0x3f,0xc0,0x00,0x00,0xff,0x00,0x3f,0xc0,0x00,0x0c,0x3f,0x0f,0xc0,0xf0,0x00,0x0c,0x3f,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x80,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x80,0x00,0x00,0x0a,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0xa0,0x00,0x00,0x29,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa5,0x68,0x00,0x00,0x25,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa5,0x68,0x00,0x00,0x25,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0xa0,0x00,0x00,0x29,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x80,0x00,0x00,0x0a,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x80,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0xaa,0xaa,0xaa,0xaa,0xaa,0xff,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0xaa,0xaa,0xaa,0xaa,0xab,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xaa,0xab,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xaa,0xbc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x0f,0x00,0x00,0xff,0xfe,0xaf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xc3,0xff,0x0f,0xff,0xfc,0x0f,0xab,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xc3,0xff,0x00,0x00,0xfc,0x0f,0xab,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xc3,0xff,0xff,0xf0,0xfc,0x0f,0xab,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0xff,0xc3,0xff,0x00,0x00,0xff,0xfe,0xaf,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xaa,0xbc,0x00,0x0a,0x80,0x00,0x00,0x2a,0xa0,0x00,0xff,0xff,0xff,0xff,0xff,0xaa,0xab,0xf0,0x00,0x29,0xa0,0x00,0x00,0x2a,0xa0,0x00,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xff,0x00,0x00,0x29,0xa0,0x00,0x00,0x02,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x0a,0x80,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

