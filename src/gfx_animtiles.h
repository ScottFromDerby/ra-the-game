#pragma once

// SPRITE_AnimTiles
#define SPRITE_AnimTilesWidth 32
#define SPRITE_AnimTilesHeight 448
#define SPRITE_AnimTilesFlags BLIT_2BPP
extern const uint8_t SPRITE_AnimTiles[3584];

static void blitHalfTile_SPRITE_AnimTiles(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_AnimTiles, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_AnimTilesWidth, SPRITE_AnimTilesFlags | flags);
}

static void blitTile_SPRITE_AnimTiles(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_AnimTiles, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_AnimTilesWidth, SPRITE_AnimTilesFlags | flags);
}

