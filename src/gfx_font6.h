#pragma once

// FONT_6px
#define FONT_6pxWidth 256
#define FONT_6pxHeight 6
#define FONT_6pxFlags BLIT_1BPP
extern const uint8_t FONT_6px[192];

static void blitHalfTile_FONT_6px(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(FONT_6px, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, FONT_6pxWidth, FONT_6pxFlags | flags);
}

static void blitTile_FONT_6px(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(FONT_6px, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, FONT_6pxWidth, FONT_6pxFlags | flags);
}

