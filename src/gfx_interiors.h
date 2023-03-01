#pragma once

// SPRITE_Interiors
#define SPRITE_InteriorsWidth 64
#define SPRITE_InteriorsHeight 192
#define SPRITE_InteriorsFlags BLIT_2BPP
extern const uint8_t SPRITE_Interiors[3072];

static void blitHalfTile_SPRITE_Interiors(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Interiors, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_InteriorsWidth, SPRITE_InteriorsFlags | flags);
}

static void blitTile_SPRITE_Interiors(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_Interiors, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_InteriorsWidth, SPRITE_InteriorsFlags | flags);
}

