#pragma once

// SPRITE_NPCs
#define SPRITE_NPCsWidth 64
#define SPRITE_NPCsHeight 256
#define SPRITE_NPCsFlags BLIT_2BPP
extern const uint8_t SPRITE_NPCs[4096];

static void blitHalfTile_SPRITE_NPCs(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_NPCs, HALFTILE * x, HALFTILE * y, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_NPCsWidth, SPRITE_NPCsFlags | flags);
}

static void blitTile_SPRITE_NPCs(int32_t x, int32_t y, uint32_t tileX, uint32_t tileY, uint32_t flags)
{
    blitSub(SPRITE_NPCs, TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE, TILESIZE * tileX, TILESIZE * tileY, SPRITE_NPCsWidth, SPRITE_NPCsFlags | flags);
}

