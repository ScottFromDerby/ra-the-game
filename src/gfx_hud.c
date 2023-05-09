#include "wasm4.h"

// SPRITE_Hud
const uint8_t SPRITE_Hud[1280] = { 0x1b,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xc0,0x00,0x00,0x2f,0xff,0xff,0xff,0x00,0x03,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0xaa,0xaa,0xaa,0x00,0x3f,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0x00,0x03,0xf0,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0xf3,0xf3,0xc0,0x00,0x3f,0xff,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x03,0xfc,0xcf,0xf0,0x00,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x03,0xff,0x3f,0xf0,0x00,0xf3,0xf3,0xc0,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x03,0xfc,0xcf,0xf0,0x03,0xfc,0xcf,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xf3,0xf3,0xf0,0x03,0xff,0x3f,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0x03,0xfc,0xcf,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0x00,0xf3,0xf3,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc3,0xf0,0xc0,0x00,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x0f,0x00,0x00,0x3f,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xf0,0x00,0x00,0x03,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbf,0xc0,0x00,0x00,0xff,0xf5,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x2f,0xf0,0xfe,0x95,0x55,0x55,0x00,0x03,0xf0,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x30,0x00,0xf9,0x55,0x55,0x55,0x00,0x3f,0xff,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x30,0x00,0xe5,0x55,0x55,0x55,0x00,0xff,0xff,0xc0,0x00,0x03,0xf0,0x00,0xc0,0x00,0x30,0x00,0xe5,0x55,0x55,0x55,0x00,0xf0,0x03,0xc0,0x00,0x3f,0xff,0x00,0x00,0x00,0x30,0x00,0xd5,0x55,0x55,0x55,0x03,0xff,0xcf,0xf0,0x00,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x03,0xff,0x3f,0xf0,0x00,0xf0,0x03,0xc0,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x03,0xfc,0xff,0xf0,0x03,0xff,0xcf,0xf0,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x03,0xf0,0x03,0xf0,0x03,0xff,0x3f,0xf0,0x56,0x65,0x5b,0x51,0x55,0xd5,0x57,0xf5,0x00,0xff,0xff,0xc0,0x03,0xfc,0xff,0xf0,0x55,0x55,0x5b,0xff,0x57,0xf5,0x5c,0x0d,0x00,0xff,0xff,0xc0,0x00,0xf0,0x03,0xc0,0x56,0x59,0x5b,0x95,0x5f,0x3d,0x5c,0xcd,0x00,0xc3,0xf0,0xc0,0x00,0xff,0xff,0xc0,0x55,0x55,0x6f,0xe5,0x5c,0x0d,0x5c,0x0d,0x00,0x3c,0x0f,0x00,0x00,0x3f,0xff,0x00,0x65,0x55,0x6d,0xf6,0x5c,0xcd,0x57,0xf5,0x00,0x03,0xf0,0x00,0x00,0x03,0xf0,0x00,0x55,0x65,0x7d,0x7b,0x5c,0x0d,0x55,0xd5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x5d,0x5f,0xfd,0x55,0xd5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe9,0x55,0x55,0x55,0x0f,0xe0,0x00,0x00,0x00,0xfc,0x3f,0x00,0x00,0x00,0x00,0x00,0xe5,0x55,0x55,0x55,0x35,0x78,0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0xd5,0x55,0x55,0x55,0xd7,0x5e,0x0c,0xc0,0x3f,0xff,0xff,0xfc,0x00,0xfc,0x3f,0x00,0xd5,0x55,0x55,0x55,0xd7,0x5e,0x03,0x00,0x3c,0xfc,0xf0,0x3c,0x0f,0xff,0xff,0xf0,0xd5,0x55,0x55,0x55,0xd7,0x5e,0x0c,0xc0,0xff,0x33,0xff,0x3f,0x3f,0xff,0xff,0xfc,0xd5,0x55,0x55,0x55,0x35,0x78,0x00,0x00,0xff,0xcf,0x3c,0xff,0x3c,0xfc,0xf0,0x3c,0xd5,0x55,0x55,0x55,0x0f,0xe0,0x00,0x00,0xff,0x33,0xf3,0xff,0xff,0x33,0xff,0x3f,0xd5,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0xfc,0xf0,0x3f,0xff,0xcf,0x3c,0xff,0xd5,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xfc,0xff,0x33,0xf3,0xff,0xd5,0x55,0x3c,0xf0,0x3c,0xf0,0x3c,0xf0,0x3f,0xff,0xff,0xfc,0x3c,0xfc,0xf0,0x3c,0xd5,0x55,0xc3,0x0c,0xd7,0x0c,0xd7,0x5c,0x30,0xfc,0x3f,0x0c,0x3f,0xff,0xff,0xfc,0xd5,0x55,0xc0,0x0c,0xd5,0x0c,0xd5,0x5c,0x0f,0x03,0xc0,0xf0,0x0f,0xff,0xff,0xf0,0xd5,0x55,0x30,0x30,0x35,0x30,0x35,0x70,0x00,0xfc,0x3f,0x00,0x00,0xfc,0x3f,0x00,0xd5,0x55,0x0c,0xc0,0x0d,0xc0,0x0d,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd5,0x55,0x03,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x55,0x57,0xd5,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x5c,0x35,0x55,0x57,0x95,0x56,0xe5,0x55,0x55,0x55,0x55,0x57,0xff,0xd5,0x55,0x55,0x5c,0x35,0x55,0x57,0xa5,0x5a,0xe5,0x57,0xff,0xff,0xf5,0x5f,0x00,0xff,0xd5,0x55,0x5c,0x35,0x55,0x57,0x6a,0xa9,0xe5,0x57,0xaa,0xaa,0xb5,0x5c,0x28,0xc0,0xf5,0x55,0x5c,0x35,0x55,0x57,0x55,0x55,0xe5,0x57,0x80,0x00,0x35,0x5c,0x80,0xc0,0x35,0x55,0x5c,0x35,0x55,0x57,0xd5,0x57,0xe5,0x57,0x80,0x00,0x35,0x5c,0x00,0xea,0x35,0x55,0x5c,0x35,0x55,0x55,0xf5,0x5f,0x95,0x57,0x83,0xff,0xf5,0x5c,0xaa,0xc0,0x35,0x55,0x5c,0x35,0x55,0x55,0x7d,0x7e,0x55,0x57,0x83,0xfc,0xf5,0x5c,0x00,0xea,0x35,0x55,0x5c,0x35,0x55,0x55,0x5f,0xf9,0x55,0x57,0x83,0xff,0xf5,0x5c,0xa0,0xea,0xb5,0x55,0x7f,0xfd,0x55,0x55,0x57,0xe5,0x55,0x57,0x83,0xcf,0xf5,0x5c,0x00,0xca,0x35,0x55,0x78,0x2d,0x55,0x55,0x57,0xe5,0x55,0x57,0x83,0xfc,0xf5,0x5c,0xff,0xc0,0x35,0x55,0x78,0x2d,0x55,0x55,0x57,0xe5,0x55,0x57,0x83,0xff,0xf5,0x5f,0xd5,0x7f,0xf5,0x55,0x5e,0xb5,0x55,0x55,0x57,0xe5,0x55,0x57,0xff,0xff,0xf5,0x55,0x55,0x55,0x55,0x55,0x5f,0xf5,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7f,0xf5,0x55,0x57,0xff,0xff,0x55,0x57,0xff,0xff,0xf5,0x55,0x55,0x55,0x55,0x57,0xc0,0x0f,0xf5,0x5f,0xac,0x03,0xd5,0x57,0xaa,0xaa,0xb5,0x57,0xff,0xff,0xf5,0x5f,0x30,0xc0,0x3d,0x5e,0xac,0x00,0xd5,0x57,0xbf,0xfe,0xb5,0x57,0x80,0xa0,0x35,0x5c,0x30,0xc0,0x0d,0x5e,0xac,0x00,0xd5,0x57,0xb0,0x0e,0xb5,0x57,0x0c,0x23,0x35,0x7c,0x2a,0x00,0x0d,0x5e,0xaf,0xff,0xd5,0x57,0xb0,0x3a,0xf5,0x57,0x33,0x03,0x35,0x70,0x28,0x00,0x0d,0x5f,0xff,0xaa,0xd5,0x57,0xb0,0x3b,0xd5,0x57,0x0c,0x33,0x35,0x70,0x28,0x00,0x0d,0x57,0x03,0xab,0x55,0x57,0xb0,0xef,0x55,0x57,0x00,0x33,0x35,0x7c,0x28,0x00,0x0d,0x57,0xc3,0xaf,0x55,0x57,0xa0,0xed,0xfd,0x57,0x3f,0x33,0x35,0x5c,0x28,0x00,0x0d,0x55,0xc3,0xad,0x55,0x57,0xaf,0xad,0xdd,0x57,0x33,0xff,0x35,0x5f,0x20,0x00,0x0d,0x55,0xf3,0xb5,0x55,0x57,0xaa,0xbd,0xfd,0x57,0x3f,0x00,0x35,0x57,0xc0,0x00,0x3d,0x55,0x73,0xb5,0x55,0x57,0xaa,0xb5,0xd5,0x57,0x00,0x2a,0xb5,0x55,0xff,0xff,0xf5,0x55,0x73,0xb5,0x55,0x57,0xff,0xf5,0xd5,0x57,0xff,0xff,0xf5,0x55,0x75,0x5d,0x55,0x55,0x5f,0xd5,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x75,0x5d,0x55,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };

