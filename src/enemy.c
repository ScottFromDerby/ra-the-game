#include "wasm4.h"
#include "enemy.h"
#include "main.h"
#include "gfx.h"

#include "tools.h"
#include "gfx_npcs.h"

struct Enemy g_Enemies[MAX_NUM_ENEMIES];

void clear_enemies()
{
    for(int i = 0 ; i < MAX_NUM_ENEMIES; ++i)
    {
        g_Enemies[i].type = ET_None;
    }
}

void add_enemy(enum EnemyType type, u8 xPos, u8 yPos)
{
    tracef("add_enemy: %d %d %d", type, xPos, yPos);
    for (int i = 0; i < MAX_NUM_ENEMIES; ++i)
    {
        if (g_Enemies[i].type == ET_None)
        {
            g_Enemies[i].type = type;
            g_Enemies[i].rc.x = xPos;
            g_Enemies[i].rc.y = yPos;
            g_Enemies[i].rc.w = TILESIZE;
            g_Enemies[i].rc.h = TILESIZE;   //  TBD
            g_Enemies[i].flags = 0;
            g_Enemies[i].ticks = 0;
            g_Enemies[i].moveTicks = 0;
            
            switch(type)
            {
                case ET_Octorok:
                    g_Enemies[i].gfxPhase = 0;
                    g_Enemies[i].logicPhase = (u8)OL_Wait;
                    g_Enemies[i].ticksToNextPhase = 1;  //  Moves to wander
                    g_Enemies[i].health = 1;
                break;
                default:
                break;
            }
            return;
        }
    }

    trace("Can't add enemy?!");
}

void tick_octorok(struct Enemy* pOcto)
{
    pOcto->ticksToNextPhase--;
    if (pOcto->ticksToNextPhase == 0)
    {
        //pOcto->flags = 2;
        if (pOcto->logicPhase == OL_Wait)
        {
            //  Pick new place to wander to
            //pOcto->flags = rand_range(0, 4);  //  Up, right, down, left
            pOcto->flags = (pOcto->flags + 1) % 4;
            //pOcto->flags = 3;
            pOcto->ticksToNextPhase = rand_range(10, 30);
            pOcto->logicPhase = OL_Wandering;
            tracef("ET_Octorok newphase: %d", pOcto->flags);
        }
        else if (pOcto->logicPhase == OL_Wandering)
        {
            //  Switch to wait (or fire)
            pOcto->ticksToNextPhase = rand_range(130, 170);
            pOcto->logicPhase = OL_Wait;
        }
    }

    if (pOcto->logicPhase == OL_Wandering)
    {
        //  Only increment moveTicks if it is wandering
        pOcto->moveTicks = (pOcto->moveTicks + 1) % 10;
        switch (pOcto->flags)
        {
            default:
            case 0:
                pOcto->rc.y--;
                break;
            case 1:
                pOcto->rc.x++;
                break;
            case 2:
                pOcto->rc.y++;
                break;
            case 3:
                pOcto->rc.x--;
                break;
        }

        //  Debug
        pOcto->rc.x = clamp(pOcto->rc.x, 1, 139);
        pOcto->rc.y = clamp(pOcto->rc.y, 1, 139);
    }

    //  Check player-collisions at this point
    if (g_damageFramesLeft == 0)
    {
        struct Rect rcPlayerColl = get_player_floor_rect();
        //gfx_debughighlightrect(rcPlayerColl);

        if (rc_intersect2(&pOcto->rc, &rcPlayerColl))
        {
            //  TBD: turn this in to actual damage state on player etc
            g_damageFramesLeft = 32;
        }
    }
    
    //gfx_debughighlightrect(pOcto->rc);
    //gfx_debughighlightrect(g_rcPlayer);
}

void tick_enemies()
{
    for (int i = 0; i < MAX_NUM_ENEMIES; ++i)
    {
        switch (g_Enemies[i].type)
        {
            case ET_Octorok:
            {
                g_Enemies[i].ticks = (g_Enemies[i].ticks + 1) % 60;
                tick_octorok(&g_Enemies[i]);
                break;
            }

            default:
            break;
        //tracef("%d", g_Enemies[i].ticksToNextPhase);
        }
    }
}

void draw_enemies()
{
    *DRAW_COLORS = 0x0421;
    for (int i = 0; i < MAX_NUM_ENEMIES; ++i)
    {
        switch(g_Enemies[i].type)
        {
            case ET_Octorok:
            {
                struct Rect rc = g_Enemies[i].rc;

                //tracef("%d", g_Enemies[i].ticks);
                bool bAltFrame = g_Enemies[i].moveTicks > 5;
                switch(g_Enemies[i].flags)
                {
                    default:
                    case 0: //  Up
                    {
                        u32 frameX = bAltFrame ? 0 : 1;
                        blitSub(SPRITE_NPCs, rc.x, rc.y, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_Y);
                        blitSub(SPRITE_NPCs, rc.x, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_Y);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_Y | BLIT_FLIP_X);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_Y | BLIT_FLIP_X);
                    }
                    break;

                    case 1: //  Right
                    {
                        u32 frameX = bAltFrame ? 2 : 4;
                        blitSub(SPRITE_NPCs, rc.x, rc.y, HALFTILE, HALFTILE, HALFTILE * (frameX + 1), HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_X);
                        blitSub(SPRITE_NPCs, rc.x, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * (frameX + 1), HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_X);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y, HALFTILE, HALFTILE, HALFTILE * (frameX), HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_X);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * (frameX), HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_X);
                    }
                    break;
                    case 2: //  Down
                    {
                        u32 frameX = bAltFrame ? 0 : 1;
                        blitSub(SPRITE_NPCs, rc.x, rc.y, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags);
                        blitSub(SPRITE_NPCs, rc.x, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_X);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * frameX, HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags | BLIT_FLIP_X);
                    }
                    break;

                    case 3: //  Left
                    {
                        u32 frameX = bAltFrame ? 2 : 4;
                        blitSub(SPRITE_NPCs, rc.x, rc.y, HALFTILE, HALFTILE, HALFTILE * (frameX), HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags);
                        blitSub(SPRITE_NPCs, rc.x, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * (frameX), HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y, HALFTILE, HALFTILE, HALFTILE * (frameX + 1), HALFTILE * 32, SPRITE_NPCsWidth, SPRITE_NPCsFlags);
                        blitSub(SPRITE_NPCs, rc.x + HALFTILE, rc.y + HALFTILE, HALFTILE, HALFTILE, HALFTILE * (frameX + 1), HALFTILE * 33, SPRITE_NPCsWidth, SPRITE_NPCsFlags);
                    }
                    break;
                }
            }
            break;
            case ET_OctorokBullet:
            break;
            default:
            break;
        }
        if (g_Enemies[i].type == ET_None)
        {
        }
    }
}

void get_enemy_rect(enum EnemyType type, struct Rect* pRc)
{
    switch(type)
    {
        case ET_Octorok:
            pRc->x = 0;
        break;
        case ET_OctorokBullet:
        break;
        default:
        break;
    }
}
