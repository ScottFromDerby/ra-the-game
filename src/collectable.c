#include "collectable.h"
#include "wasm4.h"
#include "player.h"
#include "tools.h"
#include "main.h"
#include "gfx_hud.h"

struct Collectable g_collectables[MAX_COLLECTABLES];

void clear_collectables()
{
    for( int i= 0 ; i < MAX_COLLECTABLES; ++i)
    {
        g_collectables[i].ticksLeft = 0;
    }
}

void add_collectable(enum CollectableType type, int x, int y, int ticks)
{
    tracef("add_collectable %d %d %d %d", type, x, y, ticks);
    for (int i = 0; i < MAX_COLLECTABLES; ++i)
    {
        if (g_collectables[i].ticksLeft == 0)
        {
            //  Reuse
            g_collectables[i].type = type;
            g_collectables[i].xPos = x;
            g_collectables[i].yPos = y;
            g_collectables[i].ticksLeft = ticks;
            break;
        }
    }
}

void tick_collectables()
{
    //  check collision

    for (int i = 0; i < MAX_COLLECTABLES; ++i)
    {
        if (g_collectables[i].ticksLeft > 0)
        {
            tracef("tick_collectables %d %d", i, g_collectables[i].ticksLeft);
            const int COLLISION_HALF = TILESIZE / 2;   //
            g_collectables[i].ticksLeft--;
            if ((g_playerX > g_collectables[i].xPos - COLLISION_HALF) && (g_playerX < g_collectables[i].xPos + COLLISION_HALF) &&
                (g_playerY > g_collectables[i].yPos - COLLISION_HALF) && (g_playerY < g_collectables[i].yPos + COLLISION_HALF))
            {
                tracef("tick_collectables AWARD! %d", i);
                //  Award
                switch( g_collectables[i].type )
                {
                    case COLL_Heart:
                        g_playerNumHalfHearts = clamp(g_playerNumHalfHearts + 1, 0, g_playerMaxNumHalfHearts);
                    break;
                    case COLL_Coin:
                        g_playerNumCoins++;
                    break;
                }
                g_collectables[i].ticksLeft = 0;

                //  Do anim?
            }
        }
    }
}

void draw_collectables()
{
    for (int i = 0; i < MAX_COLLECTABLES; ++i)
    {
        //tracef("draw_collectables %d %d %d", i, g_collectables[i].ticksLeft, g_collectables[i].ticksLeft % 2 == 0);
        if (g_collectables[i].ticksLeft > 120 || (g_collectables[i].ticksLeft % 8 > 4))
        {
            u32 tileX = 0;
            u32 tileY = 0;
            switch( g_collectables[i].type )
            {
                case COLL_Heart:
                    tileX = 3;
                    tileY = 5;
                break;
                case COLL_Coin:
                    tileX = 2;
                    tileY = 4;
                break;
            }
            *DRAW_COLORS = 0x4320;
            blitSub(SPRITE_Hud, g_collectables[i].xPos - 4, g_collectables[i].yPos - 4, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * tileY, SPRITE_HudWidth, SPRITE_HudFlags);
        }
    }
}