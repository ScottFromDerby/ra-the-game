#pragma once

// FONT_8px
#define FONT_8pxWidth 512
#define FONT_8pxHeight 8
#define FONT_8pxFlags BLIT_1BPP
extern const uint8_t FONT_8px[512];

static void blitHalfTile_FONT_8px(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(FONT_8px, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, FONT_8pxWidth, FONT_8pxFlags | flags);
}

static void blitTile_FONT_8px(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(FONT_8px, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, FONT_8pxWidth, FONT_8pxFlags | flags);
}

