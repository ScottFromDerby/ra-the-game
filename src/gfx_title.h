#pragma once

// SPRITE_Title
#define SPRITE_TitleWidth 64
#define SPRITE_TitleHeight 96
#define SPRITE_TitleFlags BLIT_2BPP
extern const uint8_t SPRITE_Title[1536];

static void blitHalfTile_SPRITE_Title(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Title, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_TitleWidth, SPRITE_TitleFlags | flags);
}

static void blitTile_SPRITE_Title(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Title, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_TitleWidth, SPRITE_TitleFlags | flags);
}

