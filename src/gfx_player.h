#pragma once

// SPRITE_Player
#define SPRITE_PlayerWidth 64
#define SPRITE_PlayerHeight 288
#define SPRITE_PlayerFlags BLIT_2BPP
extern const uint8_t SPRITE_Player[4608];

static void blitHalfTile_SPRITE_Player(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Player, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | flags);
}

static void blitTile_SPRITE_Player(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Player, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | flags);
}

