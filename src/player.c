#include "player.h"
#include "main.h"

#include "gfx_player.h"


void draw_player_sprite()
{
    u32 spriteSheetOffsetX = 0;
    u32 spriteSheetOffsetY = 0;
    u32 spriteSheetRenderFlags = 0;
    switch (g_currentFacing)
    {
    case Up:
        spriteSheetOffsetX = 16;
        spriteSheetOffsetY = 0;
        spriteSheetRenderFlags = (g_upHeldFrames % 16 > 8) ? BLIT_FLIP_X : 0;
        break;
    case Down:
        spriteSheetOffsetX = 0;
        spriteSheetOffsetY = 0;
        spriteSheetRenderFlags = (g_downHeldFrames % 16 > 8) ? BLIT_FLIP_X : 0;
        break;
    case Right:
        spriteSheetOffsetX = (g_rightHeldFrames % 16 > 8) ? 32 : 48;
        spriteSheetOffsetY = 0;
        spriteSheetRenderFlags = BLIT_FLIP_X;
        break;
    case Left:
        spriteSheetOffsetX = (g_leftHeldFrames % 16 > 8) ? 32 : 48;
        spriteSheetOffsetY = 0;
        spriteSheetRenderFlags = 0;
        break;
    default:
        break;
    }

    int playerExtraOffsetX = 0;
    int playerExtraOffsetY = 0;
    if (g_transitionFramesLeft > 0)
    {
        if (g_transitionDirection == Left)
        {
            playerExtraOffsetX = -g_transitionFramesLeft;
        }
        else if (g_transitionDirection == Right)
        {
            playerExtraOffsetX = g_transitionFramesLeft;
        }

        if (g_transitionDirection == Up)
        {
            playerExtraOffsetY = -g_transitionFramesLeft;
        }
        else if (g_transitionDirection == Down)
        {
            playerExtraOffsetY = g_transitionFramesLeft;
        }
    }

    *DRAW_COLORS = 0x0421;
    blitSub(SPRITE_Player, g_playerX - HALFTILE + playerExtraOffsetX, g_playerY - HALFTILE + playerExtraOffsetY, TILESIZE, TILESIZE, spriteSheetOffsetX, spriteSheetOffsetY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | spriteSheetRenderFlags);
}

void draw_weapon()
{
    
}
