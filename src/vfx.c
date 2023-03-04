#include "vfx.h"
#include "wasm4.h"
#include "tools.h"
#include "gfx_overworld.h"

struct VFXSprite g_vfx[MAX_VFX_SPRITES];

void clear_vfx()
{
    for (int i = 0; i < MAX_VFX_SPRITES; ++i)
    {
        g_vfx->ticksLeft = 0;
    }
}

void add_vfx(enum VFXType type, int x, int y, int xVel, int yVel, int ticks, u32 flags)
{
    tracef("add_vfx %d %d %d %d %d %d %d", type, x, y, xVel, yVel, ticks, flags);
    for (int i = 0; i < MAX_VFX_SPRITES; ++i)
    {
        if (g_vfx[i].ticksLeft == 0)
        {
            g_vfx[i].type = type;
            g_vfx[i].x_10 = x * 10;
            g_vfx[i].y_10 = y * 10;
            g_vfx[i].xVel = xVel;
            g_vfx[i].yVel = yVel;
            g_vfx[i].ticksLeft = ticks;
            g_vfx[i].flags = flags;
            g_vfx[i].rng = (u8)rand() + 1;
            break;
        }
    }
}

void tick_vfx()
{
    for (int i = 0; i < MAX_VFX_SPRITES; ++i)
    {
        if (g_vfx[i].ticksLeft > 0)
        {
            //tracef("tick_vfx %d", i);
            g_vfx[i].ticksLeft--;
            g_vfx[i].x_10 += g_vfx[i].xVel;
            g_vfx[i].y_10 += g_vfx[i].yVel;

            if( (g_vfx[i].x_10/10) < -HALFTILE || (g_vfx[i].x_10/10) > SCREEN_WIDTH || 
                (g_vfx[i].y_10/10) < -HALFTILE || (g_vfx[i].y_10/10) > SCREEN_HEIGHT )
            {
                //  Kill; offscreen
                g_vfx[i].ticksLeft = 0;
            }
        }
    }
}

void draw_vfx()
{
    for (int i = 0; i < MAX_VFX_SPRITES; ++i)
    {
        if (g_vfx[i].ticksLeft > 0)
        {    
            *DRAW_COLORS = 0x4320;
            
            //  Draw
            u32 tileX = 0;
            u32 tileY = 0;
            u32 flags = g_vfx[i].flags;
            switch (g_vfx[i].type)
            {
                default:
                case VFX_LeafFoliage:
                tileX = 0;
                tileY = 6;
                if (g_vfx[i].ticksLeft % 2 == 0)
                {
                    tileX = 0;
                    tileY = 0;
                }
                if ((g_vfx[i].rng % 2) == 0) //  Spinny leaf
                {
                    if (((g_vfx[i].ticksLeft + g_vfx[i].rng) % 16) < 8)
                    {
                        flags |= BLIT_FLIP_X;
                    }
                }
                else if ((g_vfx[i].rng % 3) == 0)
                {
                    //  Permanently flipped
                    flags |= BLIT_FLIP_X;
                }
                if (g_vfx[i].rng > 128)
                {
                    //  Also flipped in y
                    flags |= BLIT_FLIP_Y;
                }

                break;
            }
            
            blitSub(SPRITE_Overworld, (g_vfx[i].x_10/10), (g_vfx[i].y_10/10), HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
        }
    }
}