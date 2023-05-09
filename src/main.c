#include "wasm4.h"
#include "main.h"

#include "animtiles.h"
#include "collectable.h"
#include "dialog_data.h"
#include "dialog.h"
#include "enemy.h"
#include "gfx.h"
#include "input.h"
#include "interactables.h"
#include "mapdata.h"
#include "music.h"
#include "player.h"
#include "progress.h"
#include "rendering.h"
#include "tools.h"
#include "vfx.h"

//  Assets
#include "gfx_hud.h"
#include "gfx_npcs.h"
#include "gfx_title.h"

#define NO_SPLASH

u32 g_uTicks = 0;

u8 g_upHeldFrames = 0;
u8 g_downHeldFrames = 0;
u8 g_leftHeldFrames = 0;
u8 g_rightHeldFrames = 0;

enum Direction g_currentFacing = Down;
enum GameState g_gameState = INGAME;

u8 g_playerX = 100;
u8 g_playerY = 100;
bool g_debugPlayerSpriteAlt = false;

u8 g_damagePushX = 0;
u8 g_damagePushY = 0;
u8 g_damageFramesLeft = 0;

enum ActiveItemType
{
    AI_Sword,
    AI_Slingshot,
    AI_Item3,
    AI_Item4,
    AI_NUM_ACTIVE_ITEM_TYPES,
    AI_None = -1
};

enum PassiveItemType
{
    PI_Shield,
    PI_SlingshotP,
    PI_Item3,
    PI_Item4,
    PI_None
};

enum ActiveItemType g_selectedActiveItem = AI_Sword;
enum PassiveItemType g_selectedPassiveItem = PI_None;
int g_pauseCursorIndexX = 0;
int g_pauseCursorIndexY = 0;

struct ScreenMeta g_currentScreen;
struct ScreenMeta g_transitionFromScreen;
u8 g_currentWorldX = (u8)-1;
u8 g_currentWorldY = (u8)-1;
int g_transitionFramesLeft = 0;
enum Direction g_transitionDirection = Left;

enum PauseState
{
    Off,
    Entering,
    Visible,
    Leaving,
};
enum PauseState g_pauseState;
int g_pauseStateFramesLeft = 0;

void toggle_pause()
{
    if (g_pauseState == Off)
    {
        g_pauseState = Entering;
        g_pauseStateFramesLeft = SCREEN_HEIGHT;
        g_gameState = PAUSE;
    }
    else if (g_pauseState == Visible)
    {
        g_pauseState = Leaving;
        g_pauseStateFramesLeft = SCREEN_HEIGHT;
    }
}

void tick_pause()
{
    if (g_pauseStateFramesLeft > 0 && ((g_pauseState == Entering) || (g_pauseState == Leaving)))
    {
        g_pauseStateFramesLeft -= 8;
        if( g_pauseStateFramesLeft == 0 )
        {
            if( g_pauseState == Entering )
            {
                g_pauseState = Visible;
            }
            if (g_pauseState == Leaving)
            {
                g_pauseState = Off;
                g_gameState = INGAME;
            }
        }
    }

    if (g_pauseState == Visible)
    {
        if (button_newly_pressed(BUTTON_DOWN))
        {
            if (g_pauseCursorIndexY < 3)
            {
                g_pauseCursorIndexY++;
                //  sound
            }
        }
        else if (button_newly_pressed(BUTTON_UP))
        {
            if (g_pauseCursorIndexY > 0)
            {
                g_pauseCursorIndexY--;
                //  sound
            }
        }
        else if (button_newly_pressed(BUTTON_RIGHT))
        {
            if (g_pauseCursorIndexX < 1)
            {
                g_pauseCursorIndexX++;
                //  sound
            }
        }
        else if (button_newly_pressed(BUTTON_LEFT))
        {
            if (g_pauseCursorIndexX > 0)
            {
                g_pauseCursorIndexX--;
                //  sound
            }
        }
        else if (button_newly_pressed(BUTTON_1))
        {
            if (g_pauseCursorIndexX == 0)
            {
                //  Change selected active weapon
                if( g_selectedPassiveItem != (enum PassiveItemType)g_pauseCursorIndexY )
                {
                    g_selectedPassiveItem = (enum PassiveItemType)g_pauseCursorIndexY;
                }
                else
                {
                    g_selectedPassiveItem = PI_None;
                }
            }
            else if (g_pauseCursorIndexX == 1)
            {
                //  Change selected passive weapon
                
                if( g_selectedActiveItem != (enum ActiveItemType)g_pauseCursorIndexY )
                {
                    g_selectedActiveItem = (enum ActiveItemType)g_pauseCursorIndexY;
                }
                else
                {
                    g_selectedActiveItem = AI_None;
                }
            }
        }
        else if (button_newly_pressed(BUTTON_2))
        {
            toggle_pause();
        }
    }
}

void draw_pause()
{
    if (g_pauseState == Off)
    {
        return;
    }

    int yOffset = 0;
    if (g_pauseState == Entering)
    {
        yOffset = g_pauseStateFramesLeft;
    }
    else if (g_pauseState == Leaving)
    {
        yOffset = SCREEN_HEIGHT - g_pauseStateFramesLeft;
    }

    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        for (int j = yOffset; j < SCREEN_HEIGHT; ++j)
        {
            gfx_setpixel(i, j, 0x1234);
        }
    }

    gfx_drawstr("Passive", 94, 35 + yOffset, 0x0030, false);
    gfx_drawstr("Active", 126, 35 + yOffset, 0x0030, false);

    *DRAW_COLORS = 0x3240;

    //  Draw borders
    blitSub(SPRITE_Hud, HALFTILE * 0, HALFTILE * 0 + yOffset, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags);
    blitSub(SPRITE_Hud, HALFTILE * 19, HALFTILE * 0 + yOffset, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X);
    blitSub(SPRITE_Hud, HALFTILE * 0, HALFTILE * 17 + yOffset, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_Y);
    blitSub(SPRITE_Hud, HALFTILE * 19, HALFTILE * 17 + yOffset, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X | BLIT_FLIP_Y);
    for (int i = 1; i < 19; ++i)
    {
        blitSub(SPRITE_Hud, HALFTILE * i, HALFTILE * 0 + yOffset, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags);
        blitSub(SPRITE_Hud, HALFTILE * i, HALFTILE * 17 + yOffset, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_Y);
    }
    for (int i = 1; i < 17; ++i)
    {
        blitSub(SPRITE_Hud, HALFTILE * 0, HALFTILE * i + yOffset, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_ROTATE);
        blitSub(SPRITE_Hud, HALFTILE * 19, HALFTILE * i + yOffset, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_ROTATE | BLIT_FLIP_Y);
    }

    *DRAW_COLORS = 0x4321;

    //  Passive
    for (int i = 0; i < 4; ++i)
    {
        *DRAW_COLORS = 0x4301;
        if (g_selectedPassiveItem == (enum PassiveItemType)i)
        {
            *DRAW_COLORS = 0x4321;
        }
        blitHalfTileOffs_SPRITE_Hud(12, 6 + (i * 3), 0, yOffset, 0, 4, 0);
        blitHalfTileOffs_SPRITE_Hud(13, 6 + (i * 3), 0, yOffset, 0, 5, BLIT_ROTATE | BLIT_FLIP_X);
        blitHalfTileOffs_SPRITE_Hud(14, 6 + (i * 3), 0, yOffset, 0, 4, BLIT_FLIP_X);
        blitHalfTileOffs_SPRITE_Hud(12, 7 + (i * 3), 0, yOffset, 0, 4, BLIT_FLIP_Y);
        blitHalfTileOffs_SPRITE_Hud(13, 7 + (i * 3), 0, yOffset, 0, 5, BLIT_ROTATE);
        blitHalfTileOffs_SPRITE_Hud(14, 7 + (i * 3), 0, yOffset, 0, 4, BLIT_FLIP_X | BLIT_FLIP_Y);
    }

    //  Active
    for (int i = 0; i < 4; ++i)
    {
        *DRAW_COLORS = 0x4301;
        if (g_selectedActiveItem == (enum ActiveItemType)i)
        {
            *DRAW_COLORS = 0x4321;
        }
        blitHalfTileOffs_SPRITE_Hud(16, 6 + (i * 3), 0, yOffset, 0, 4, 0);
        blitHalfTileOffs_SPRITE_Hud(17, 6 + (i * 3), 0, yOffset, 0, 5, BLIT_ROTATE | BLIT_FLIP_X);
        blitHalfTileOffs_SPRITE_Hud(18, 6 + (i * 3), 0, yOffset, 0, 4, BLIT_FLIP_X);
        blitHalfTileOffs_SPRITE_Hud(16, 7 + (i * 3), 0, yOffset, 0, 4, BLIT_FLIP_Y);
        blitHalfTileOffs_SPRITE_Hud(17, 7 + (i * 3), 0, yOffset, 0, 5, BLIT_ROTATE);
        blitHalfTileOffs_SPRITE_Hud(18, 7 + (i * 3), 0, yOffset, 0, 4, BLIT_FLIP_X | BLIT_FLIP_Y);
    }

    //  Draw items:
    //  Sword
    *DRAW_COLORS = g_selectedActiveItem == AI_Sword ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 8 + 4, HALFTILE * 6 + yOffset, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 3, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Slingshot
    *DRAW_COLORS = g_selectedActiveItem == AI_Slingshot ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 8 + 4, HALFTILE * 9 + yOffset, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 3, SPRITE_HudWidth, SPRITE_HudFlags);

    //  ActiveItem3
    *DRAW_COLORS = g_selectedActiveItem == AI_Item3 ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 8 + 4, HALFTILE * 12 + yOffset, TILESIZE, TILESIZE, TILESIZE * 2, TILESIZE * 3, SPRITE_HudWidth, SPRITE_HudFlags);

    //  ActiveItem4
    *DRAW_COLORS = g_selectedActiveItem == AI_Item4 ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 8 + 4, HALFTILE * 15 + yOffset, TILESIZE, TILESIZE, TILESIZE * 3, TILESIZE * 3, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Passive Items:
    //  Shield
    *DRAW_COLORS = g_selectedPassiveItem == PI_Shield ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 6 + 4, HALFTILE * 6 + yOffset, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 4, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Passive2
    *DRAW_COLORS = g_selectedPassiveItem == PI_SlingshotP ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 6 + 4, HALFTILE * 9 + yOffset, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 4, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Passive3
    *DRAW_COLORS = g_selectedPassiveItem == PI_Item3 ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 6 + 4, HALFTILE * 12 + yOffset, TILESIZE, TILESIZE, TILESIZE * 2, TILESIZE * 4, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Passive4
    *DRAW_COLORS = g_selectedPassiveItem == PI_Item4 ? 0x4321 : 0x4301;
    blitSub(SPRITE_Hud, TILESIZE * 6 + 4, HALFTILE * 15 + yOffset, TILESIZE, TILESIZE, TILESIZE * 3, TILESIZE * 4, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Draw cursor:
    *DRAW_COLORS = 0x4300; //  0x4320 = White = transparent
    // blitSub(SPRITE_Hud, TILESIZE * 7 + 12, TILESIZE * 4 + yOffset, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 3, SPRITE_HudWidth, SPRITE_HudFlags);

    u32 xAnimFrame = (g_uTicks % 20 > 7) ? 0 : 1;

    int xCursorOffs = (g_pauseCursorIndexX == 0) ? 12 : 16;
    int yCursorOffs = 6 + (g_pauseCursorIndexY * 3);

    blitHalfTileOffs_SPRITE_Hud(xCursorOffs, yCursorOffs, -3, yOffset - 3, xAnimFrame, 2, 0);
    blitHalfTileOffs_SPRITE_Hud(xCursorOffs + 2, yCursorOffs, 3, yOffset - 3, xAnimFrame, 2, BLIT_FLIP_X);
    blitHalfTileOffs_SPRITE_Hud(xCursorOffs, yCursorOffs + 2, -3, yOffset - 5, xAnimFrame, 2, BLIT_FLIP_Y);
    blitHalfTileOffs_SPRITE_Hud(xCursorOffs + 2, yCursorOffs + 2, 3, yOffset - 5, xAnimFrame, 2, BLIT_FLIP_X | BLIT_FLIP_Y);

    *DRAW_COLORS = 0x4321; //  0x4320 = White = transparent
    const int MapTLX = 15;
    const int MapTLY = 64;
    for (int j = 0; j < WORLD_MAX_Y; ++j)
    {
        for (int i = 0; i < WORLD_MAX_X; ++i)
        {
            u32 xSprite = 0;
            u32 ySprite = 3;
            if (i == 2 && j == 2)
            {
                xSprite = 2;
            }
            else if (i == 2 && j == 1)
            {
                xSprite = 3;
            }
            else if (i == 1 && j == 2)
            {
                xSprite = 3;
            }
            else if (i == 1 && j == 3)
            {
                xSprite = 3;
            }

            if (i == g_currentWorldX && j == g_currentWorldY)
            {
                //  Here
                *DRAW_COLORS = (g_uTicks % 25 > 10) ? 0x4321 : 0x0021;
                blitHalfTileOffs_SPRITE_Hud(i, j, MapTLX, MapTLY + yOffset, xSprite, ySprite, 0);
            }
            else
            {
                *DRAW_COLORS = 0x4321;
                blitHalfTileOffs_SPRITE_Hud(i, j, MapTLX, MapTLY + yOffset, xSprite, ySprite, 0);
            }
        }
    }

    //  Gridlines over map
    for (int j = 0; j < (WORLD_MAX_X + 1); ++j)
    {
        for (int i = 0; i < (WORLD_MAX_X * HALFTILE) + 1; ++i)
        {
            gfx_setpixel(MapTLX + (j * 8), MapTLY + i + yOffset, 0x3);
            gfx_setpixel(MapTLX + i, MapTLY + (j * 8) + yOffset, 0x3);
        }
    }
}

bool is_tile_blocked_by_npc(u8 x, u8 y)
{
    for( int i = 0; i < NUM_INTERACTABLES; ++i )
    {
        if( ((g_Interactables[i].interactableFlags & INTERACTABLE_BLOCK_PLAYER) != 0) &&
            (g_Interactables[i].xPos == x) && 
            (g_Interactables[i].yPos == y))
        {
            //trace("Blocked by NPC");
            return true;
        }
    }
    return false;
}

void on_start_screen()
{
    g_Progress.visited[g_currentWorldX + (g_currentWorldY * WORLD_MAX_X)] = true;

    // clear_foliage();
    
    // for (int i = 0; i < NUM_TILES_HEIGHT; ++i)
    // {
    //     for (int j = 0; j < NUM_TILES_WIDTH; ++j)
    //     {
    //         if (g_currentScreen.screen_metatiles[i * NUM_TILES_HEIGHT + j] == TGrs)
    //         {
    //             add_foliage(i, j, Foliage_TallGrass);
    //         }
    //     }
    // }

    switch (g_currentWorldX | (g_currentWorldY << 4))   //  NB. this = 0x[X][Y] for world pos
    {
        case 0x12:
        add_interactable(IT_RA_NPC01, 2, 1, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);
        add_interactable(IT_RA_NPC02, 1, 5, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);
        add_interactable(IT_RA_NPC03, 8, 2, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);
        add_interactable(IT_RA_NPC04, 7, 6, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);
        break;
        case 0x20:
        //trace("left2");
        break;
        case 0x21:
        //trace("left");
        add_interactable(IT_AnotherNPC, 4, 4, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);
        break;
        case 0x22:
        //trace("start");
        add_anim_tile(ATT_Flower, 16, 12, 0);
        add_anim_tile(ATT_Flower, 17, 13, 2);
        add_anim_tile(ATT_Flower, 4, 10, 0);
        add_anim_tile(ATT_Flower, 5, 11, 2);
        add_anim_tile(ATT_Flower, 12, 4, 0);
        add_anim_tile(ATT_Flower, 13, 5, 2);
        add_interactable(IT_StartTestNPC, 7, 3, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);

        add_interactable(IT_MusicBox, 4, 4, INTERACTABLE_ACTIVE | INTERACTABLE_BLOCK_PLAYER);
        //add_anim_tile(ATT_MusicBox, 8, 2, 0);
        break;
        case 0x31:
        add_enemy(ET_Octorok, 40, 40);
        break;
    }

    save_game();

    g_debugPlayerSpriteAlt = !g_debugPlayerSpriteAlt;
}

void clear_screen()
{
    for (int i = 0; i < NUM_ANIM_TILES; ++i)
    {
        g_AnimTiles[i].type = ATT_None;
        g_AnimTiles[i].ticks = 0;
    }
    //  Clear NPC
    clear_interactables();
    clear_collectables();
    clear_enemies();
}

void set_screen(u8 x, u8 y, bool bForce)
{
    //tracef("doing set_screen %d %d %d %d", x, y, g_currentWorldX, g_currentWorldY);

    clear_screen();

    if (bForce)
    {
        copy_screen(get_screen(x, y), &g_currentScreen);
        g_currentWorldX = x;
        g_currentWorldY = y;
        on_start_screen();
    }
    else
    {
        g_Progress.bHasVisitedOtherScreens = true;

        g_transitionFromScreen = g_currentScreen;
        copy_screen(get_screen(x, y), &g_currentScreen);
        //g_currentScreen = get_screen(x, y);
        if (x > g_currentWorldX)
        {
            g_transitionFramesLeft = SCREEN_WIDTH;
            g_transitionDirection = Right;
        }
        else if (x < g_currentWorldX)
        {
            g_transitionFramesLeft = SCREEN_WIDTH;
            g_transitionDirection = Left;
        }
        else if (y < g_currentWorldY)
        {
            g_transitionFramesLeft = SCREEN_HEIGHT;
            g_transitionDirection = Up;
        }
        else if (y > g_currentWorldY)
        {
            g_transitionFramesLeft = SCREEN_HEIGHT;
            g_transitionDirection = Down;
        }
        else
        {
            trace("Unknown transition direction!");
        }
        g_currentWorldX = x;
        g_currentWorldY = y;
    }
}

void update_room()
{
    //if (g_currentScreen == 0)
    if(g_currentWorldX >= WORLD_MAX_X || g_currentWorldY >= WORLD_MAX_Y )
    {
        trace("Setting initial screen");
        set_screen(START_WORLD_X, START_WORLD_Y, true);
    }
    //  Update transitions
    if (g_transitionFramesLeft > 0)
    {
        g_transitionFramesLeft -= 4;
        if (g_transitionFramesLeft == 0)
        {
            on_start_screen();
        }
    }
    tick_animated_tiles();
}

void draw_room()
{
    *DRAW_COLORS = 0x4321;

    if (g_transitionFramesLeft > 0)
    {
        if (g_transitionDirection == Left || g_transitionDirection == Right)
        {
            int xOffset = (g_transitionDirection == Left) ? -g_transitionFramesLeft : g_transitionFramesLeft;

            //  Moving to the left - move screen to the right
            for (uint8_t i = 0; i < NUM_TILES_WIDTH; ++i)
            {
                for (uint8_t j = 0; j < NUM_TILES_HEIGHT; ++j)
                {
                    draw_metatile(i, j, get_meta_tile(i, j), 0, xOffset, 0);
                }
            }

            xOffset = (g_transitionDirection == Left) ? SCREEN_WIDTH - g_transitionFramesLeft : -SCREEN_WIDTH + g_transitionFramesLeft;
            for (uint8_t i = 0; i < NUM_TILES_WIDTH; ++i)
            {
                for (uint8_t j = 0; j < NUM_TILES_HEIGHT; ++j)
                {
                    draw_metatile(i, j, get_meta_tile_transition(i, j), 0, xOffset, 0);
                }
            }
        }
        else if (g_transitionDirection == Up || g_transitionDirection == Down)
        {
            int yOffset = (g_transitionDirection == Up) ? -g_transitionFramesLeft : g_transitionFramesLeft;

            //  Moving to the left - move screen to the right
            uint8_t TL = 0;
            uint8_t TR = 0;
            uint8_t BL = 0;
            uint8_t BR = 0;
            for (uint8_t i = 0; i < NUM_TILES_WIDTH; ++i)
            {
                for (uint8_t j = 0; j < NUM_TILES_HEIGHT; ++j)
                {
                    u32 flags = get_meta_tile_info(get_meta_tile(i, j), &TL, &TR, &BL, &BR);
                    draw_halftile(i * 2, j * 2, (u32)TL, flags, 0, yOffset);
                    draw_halftile(i * 2 + 1, j * 2, (u32)TR, flags, 0, yOffset);
                    draw_halftile(i * 2, j * 2 + 1, (u32)BL, flags, 0, yOffset);
                    draw_halftile(i * 2 + 1, j * 2 + 1, (u32)BR, flags, 0, yOffset);
                }
            }

            yOffset = (g_transitionDirection == Up) ? SCREEN_HEIGHT - g_transitionFramesLeft : -SCREEN_HEIGHT + g_transitionFramesLeft;
            for (uint8_t i = 0; i < NUM_TILES_WIDTH; ++i)
            {
                for (uint8_t j = 0; j < NUM_TILES_HEIGHT; ++j)
                {
                    u32 flags = get_meta_tile_info(get_meta_tile_transition(i, j), &TL, &TR, &BL, &BR);
                    draw_halftile(i * 2, j * 2, (u32)TL, flags, 0, yOffset);
                    draw_halftile(i * 2 + 1, j * 2, (u32)TR, flags, 0, yOffset);
                    draw_halftile(i * 2, j * 2 + 1, (u32)BL, flags, 0, yOffset);
                    draw_halftile(i * 2 + 1, j * 2 + 1, (u32)BR, flags, 0, yOffset);
                }
            }
        }
    }
    else
    {
        uint8_t TL = 0;
        uint8_t TR = 0;
        uint8_t BL = 0;
        uint8_t BR = 0;
        for (uint8_t i = 0; i < 10; ++i)
        {
            for (uint8_t j = 0; j < 9; ++j)
            {
                u32 flags = get_meta_tile_info(get_meta_tile(i, j), &TL, &TR, &BL, &BR);
                draw_halftile(i * 2, j * 2, (u32)TL, flags, 0, 0);
                draw_halftile(i * 2 + 1, j * 2, (u32)TR, flags, 0, 0);
                draw_halftile(i * 2, j * 2 + 1, (u32)BL, flags, 0, 0);
                draw_halftile(i * 2 + 1, j * 2 + 1, (u32)BR, flags, 0, 0);
            }
        }
    }

    *DRAW_COLORS = 0x0002;

    //  draw animated tiles
    for (int i = 0; i < NUM_ANIM_TILES; ++i)
    {
        switch (g_AnimTiles[i].type)
        {
            case ATT_None:
            break;

            case ATT_Flower:
                draw_animtile(g_AnimTiles[i].xPos, g_AnimTiles[i].yPos, 0x23 + (0x4 * g_AnimTiles[i].phase), 0, 0, 0);
            break;
        }
    }
}

void draw_interactables()
{
    for (int i = 0; i < NUM_INTERACTABLES; ++i)
    {
        //tracef("draw_interactables %d (%d)", i, g_Interactables[i].type);
        switch (g_Interactables[i].type)
        {
        case IT_None:
            break;
        case IT_StartTestNPC:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, 0, TILESIZE * 4, SPRITE_NPCsWidth, f);
            break;
        }
        case IT_AnotherNPC:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, 0, TILESIZE * 14, SPRITE_NPCsWidth, f);
            break;
        }
        case IT_MusicBox:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 7, SPRITE_NPCsWidth, f);
            break;
        }
        case IT_RA_NPC01:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 0, SPRITE_NPCsWidth, f);
            break;
        }
        case IT_RA_NPC02:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, TILESIZE * 2, TILESIZE * 0, SPRITE_NPCsWidth, f);
            break;
        }
        case IT_RA_NPC03:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, TILESIZE * 3, TILESIZE * 0, SPRITE_NPCsWidth, f);
            break;
        }
        case IT_RA_NPC04:
        {
            *DRAW_COLORS = 0x0421;
            u32 f = SPRITE_NPCsFlags | ((g_Interactables[i].gfxPhase == 0) ? 0 : BLIT_FLIP_X);
            blitSub(SPRITE_NPCs, g_Interactables[i].xPos * TILESIZE, g_Interactables[i].yPos * TILESIZE, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 1, SPRITE_NPCsWidth, f);
            break;
        }
        }
    }
}

void draw_player()
{
    draw_player_sprite();
    draw_weapon();
}

void draw_statusbar()
{
    *DRAW_COLORS = 0x0021;
    //  Clear
    for (int i = 0; i < 20; ++i)
    {
        draw_metatile(i, 9, Empt, 0, 0, 0);
    }

    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        gfx_setpixel(i, SCREEN_HEIGHT, 0x0003);
    }


    //  Micromap
    const int MapX = 4;
    const int MapY = 149;
    const int col_white = 0x0000;
    const int col_visited = 0x0001;
    const int col_unknown = 0x0002;
    const int col_black = 0x0003;

    for (int i = 0; i < WORLD_MAX_X + 2; ++i)
    {
        gfx_setpixel(MapX + i - 1, MapY - 1, col_black);
        gfx_setpixel(MapX + i - 1, MapY + 8, col_black);
    }
    for (int i = 0; i < WORLD_MAX_Y + 2; ++i)
    {
        gfx_setpixel(MapX - 1, MapY + i - 1, col_black);
        gfx_setpixel(MapX + 8, MapY + i - 1, col_black);
    }

    for (int i = 0; i < WORLD_MAX_X; ++i)
    {
        for (int j = 0; j < WORLD_MAX_Y; ++j)
        {
            if (i == g_currentWorldX && j == g_currentWorldY)
            {
                //  Local pixel
                gfx_setpixel(MapX + i, MapY + j, (g_uTicks % 40 < 20) ? col_visited : col_white);
            }
            else
            {
                //  Visited?
                gfx_setpixel(MapX + i, MapY + j, g_Progress.visited[i + j * WORLD_MAX_X] ? col_visited : col_unknown);
            }
        }
    }

    char buffer[16];

    // tostr(buffer, sizeof(*MainWorldMap.World[0]));
    // gfx_drawstr(buffer, 64, 152, 0x21, false);

    //tostr(buffer, g_playerX);
    //gfx_drawstr(buffer, 1, 152, 0x21, false);
    //tostr(buffer, g_playerY);
    //gfx_drawstr(buffer, 14, 152, 0x21, false);

    //tostr(buffer, g_currentWorldX);
    //gfx_drawstr(buffer, 27, 152, 0x31, false);
    //tostr(buffer, g_currentWorldY);
    //gfx_drawstr(buffer, 41, 152, 0x31, false);
    
    //tostr(buffer, (int)g_gameState);
    //gfx_drawstr(buffer, 57, 152, 0x31, false);

    //tostr(buffer, (int)g_pauseState);
    //gfx_drawstr(buffer, 67, 152, 0x31, false);

    //tostr(buffer, (int)g_pauseStateFramesLeft);
    //gfx_drawstr(buffer, 77, 152, 0x31, false);

    //tostr(buffer, (int)g_gamepad);
    //gfx_drawstr(buffer, 87, 152, 0x31, false);

    //tostr(buffer, (int)g_swordSwingState);
    //gfx_drawstr(buffer, 87, 152, 0x31, false);

    //tostr(buffer, sizeof(DLG_IDLOOKUP));
    //gfx_drawstr(buffer, 87, 152, 0x31, false);


    //  Inventory
    //  No transparency
    *DRAW_COLORS = 0x4321;

    blitHalfTile_SPRITE_Hud(12, 18, 0, 4, 0);
    blitHalfTile_SPRITE_Hud(12, 19, 0, 4, BLIT_FLIP_Y);
    blitHalfTile_SPRITE_Hud(13, 18, 0, 5, BLIT_ROTATE | BLIT_FLIP_X);
    blitHalfTile_SPRITE_Hud(13, 19, 0, 5, BLIT_ROTATE);
    blitHalfTile_SPRITE_Hud(14, 18, 0, 4, BLIT_FLIP_X);
    blitHalfTile_SPRITE_Hud(14, 19, 0, 4, BLIT_FLIP_X | BLIT_FLIP_Y);

    blitHalfTile_SPRITE_Hud(16, 18, 0, 4, 0);
    blitHalfTile_SPRITE_Hud(16, 19, 0, 4, BLIT_FLIP_Y);
    blitHalfTile_SPRITE_Hud(17, 18, 0, 5, BLIT_ROTATE | BLIT_FLIP_X);
    blitHalfTile_SPRITE_Hud(17, 19, 0, 5, BLIT_ROTATE);
    blitHalfTile_SPRITE_Hud(18, 18, 0, 4, BLIT_FLIP_X);
    blitHalfTile_SPRITE_Hud(18, 19, 0, 4, BLIT_FLIP_X | BLIT_FLIP_Y);

    //  Inventory Item
    //  Active:
    if (g_selectedActiveItem != AI_None)
    {
        *DRAW_COLORS = 0x4321;  //  0x4320 = White = transparent
        blitSub(SPRITE_Hud, TILESIZE * 8 + 4, TILESIZE * 9, TILESIZE, TILESIZE, TILESIZE * (u32)g_selectedActiveItem, TILESIZE * 3, SPRITE_HudWidth, SPRITE_HudFlags);
    }

    //  Passive:
    if (g_selectedPassiveItem != PI_None)
    {
        *DRAW_COLORS = 0x4321;  //  0x4320 = White = transparent
        blitSub(SPRITE_Hud, TILESIZE * 6 + 4, TILESIZE * 9, TILESIZE, TILESIZE, TILESIZE * (u32)g_selectedPassiveItem, TILESIZE * 4, SPRITE_HudWidth, SPRITE_HudFlags);
    }

    *DRAW_COLORS = 0x4320;  //  0x4320 = White = transparent

    //  Hearts
    const int HEART_E = 1;  //  Empty
    const int HEART_H = 2;  //  Half
    const int HEART_F = 3;  //  Full
    int numHeartsReq = 2;

    u32 tileX = 0;
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 2, HALFTILE * 18 + 0, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 3, HALFTILE * 18 + 0, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 4, HALFTILE * 18 + 0, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 5, HALFTILE * 18 + 0, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 6, HALFTILE * 18 + 0, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 7, HALFTILE * 18 + 0, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 2, HALFTILE * 18 + 7, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 3, HALFTILE * 18 + 7, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 4, HALFTILE * 18 + 7, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 5, HALFTILE * 18 + 7, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 6, HALFTILE * 18 + 7, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);
    tileX = g_playerNumHalfHearts >= (numHeartsReq) ? HEART_F : g_playerNumHalfHearts >= (numHeartsReq - 1) ? HEART_H : HEART_E; numHeartsReq += 2;
    blitSub(SPRITE_Hud, HALFTILE * 7, HALFTILE * 18 + 7, HALFTILE, HALFTILE, HALFTILE * tileX, HALFTILE * 5, SPRITE_HudWidth, SPRITE_HudFlags);

    //  Currency
    blitSub(SPRITE_Hud, HALFTILE * 8 + 4, HALFTILE * 18 + 4, HALFTILE, HALFTILE, HALFTILE * 2, HALFTILE * 4, SPRITE_HudWidth, SPRITE_HudFlags);
    blitSub(SPRITE_Hud, HALFTILE * 9 + 4, HALFTILE * 18 + 4, HALFTILE, HALFTILE, HALFTILE * 3, HALFTILE * 4, SPRITE_HudWidth, SPRITE_HudFlags);
    
    tostr(buffer, g_playerNumCoins);
    gfx_drawstr(buffer, HALFTILE * 10 + 4, HALFTILE * 18 + 5, 0x41, false);

    //  Frames
    tostr(buffer, (int)g_uTicks % 60);
    gfx_drawstr(buffer, SCREEN_WIDTH+1, 153, 0x21, true);
}

void process_player_movement()
{
    if (g_bShowingDialogBG)
    {
        return;
    }

    if (g_transitionFramesLeft > 0)
    {
        return;
    }

    if( g_swordSwingState != Swing_Off)
    {
        return;
    }

    bool bWantsMoveRight = false;
    bool bWantsMoveLeft = false;
    bool bWantsMoveDown = false;
    bool bWantsMoveUp = false;

    //  Process player movement
    if (g_gameState == INGAME)
    {
        if (button_held(BUTTON_RIGHT))
        {
            bWantsMoveRight = true;
            g_leftHeldFrames = 0;
            g_rightHeldFrames++;
            if (g_upHeldFrames == 0 && g_downHeldFrames == 0)
            {
                g_currentFacing = Right;
            }
        }
        else if (button_held(BUTTON_LEFT))
        {
            bWantsMoveLeft = true;
            g_rightHeldFrames = 0;
            g_leftHeldFrames++;
            if (g_upHeldFrames == 0 && g_downHeldFrames == 0)
            {
                g_currentFacing = Left;
            }
        }
        else
        {
            g_leftHeldFrames = 0;
            g_rightHeldFrames = 0;
        }
        if (button_held(BUTTON_DOWN))
        {
            bWantsMoveDown = true;
            g_upHeldFrames = 0;
            g_downHeldFrames++;
            if (g_leftHeldFrames == 0 && g_rightHeldFrames == 0)
            {
                g_currentFacing = Down;
            }
        }
        else if (button_held(BUTTON_UP))
        {
            bWantsMoveUp = true;
            g_downHeldFrames = 0;
            g_upHeldFrames++;
            if (g_leftHeldFrames == 0 && g_rightHeldFrames == 0)
            {
                g_currentFacing = Up;
            }
        }
        else
        {
            g_upHeldFrames = 0;
            g_downHeldFrames = 0;
        }
    }

    //  Test for wall bounding; if space is free, move to it!
    //  NB. Here is the actual player sprite.
    //   o = sprite, P = center (where g_playerX/Y refers to)
    //   the inner rect is the area we use for collisions below
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooooooooooooooo
    //  oooo----P----ooo
    //  oooo|ooooooo|ooo
    //  oooo|ooooooo|ooo
    //  oooo|ooooooo|ooo
    //  oooo|ooooooo|ooo
    //  oooo|ooooooo|ooo
    //  oooo---------ooo
    //  oooooooooooooooo
    if (bWantsMoveLeft)
    {
        u8 newX1, newY1, newX2, newY2;
        get_tile_from_point(g_playerX - 4 - 1, g_playerY - 0, &newX1, &newY1);
        get_tile_from_point(g_playerX - 4 - 1, g_playerY + 6, &newX2, &newY2);

        //  If my left side is allowed near my top and bottom to move onto the
        //   tile to the left of me, do so
        if (can_move_onto_tile(get_meta_tile(newX1, newY1)) &&
            can_move_onto_tile(get_meta_tile(newX2, newY2)) &&
            !is_tile_blocked_by_npc(newX1, newY1) &&
            !is_tile_blocked_by_npc(newX2, newY2))
        {
            g_playerX--;
        }
        else
        {
            //trace("blocking left");
        }
    }
    else if (bWantsMoveRight)
    {
        u8 newX1, newY1, newX2, newY2;
        get_tile_from_point(g_playerX + 4 + 1, g_playerY - 0, &newX1, &newY1);
        get_tile_from_point(g_playerX + 4 + 1, g_playerY + 6, &newX2, &newY2);
        //  If my right side is allowed near the top and bottom to move onto the
        //   tile to the left of me, do so
        if (can_move_onto_tile(get_meta_tile(newX1, newY1)) &&
            can_move_onto_tile(get_meta_tile(newX2, newY2)) &&
            !is_tile_blocked_by_npc(newX1, newY1) &&
            !is_tile_blocked_by_npc(newX2, newY2))
        {
            g_playerX++;
        }
        else
        {
            //trace("blocking right");
        }
    }

    if (bWantsMoveUp)
    {
        u8 newX1, newY1, newX2, newY2;
        get_tile_from_point(g_playerX - 4, g_playerY - 0 - 1, &newX1, &newY1);
        get_tile_from_point(g_playerX + 4, g_playerY - 0 - 1, &newX2, &newY2);
        //  If my top side is allowed near my top left and right to move onto the
        //   tile above me, do so
        if (can_move_onto_tile(get_meta_tile(newX1, newY1)) &&
            can_move_onto_tile(get_meta_tile(newX2, newY2)) &&
            !is_tile_blocked_by_npc(newX1, newY1) &&
            !is_tile_blocked_by_npc(newX2, newY2))
        {
            g_playerY--;
        }
        else
        {
            //trace("blocking top");
        }
    }
    else if (bWantsMoveDown)
    {
        u8 newX1, newY1, newX2, newY2;
        get_tile_from_point(g_playerX - 4, g_playerY + 6 + 1, &newX1, &newY1);
        get_tile_from_point(g_playerX + 4, g_playerY + 6 + 1, &newX2, &newY2);

        //  If my bottom side is allowed near the bottom left and right to move onto the
        //   tile below me, do so
        if (can_move_onto_tile(get_meta_tile(newX1, newY1)) &&
            can_move_onto_tile(get_meta_tile(newX2, newY2)) &&
            !is_tile_blocked_by_npc(newX1, newY1) &&
            !is_tile_blocked_by_npc(newX2, newY2))
        {
            g_playerY++;
        }
        else
        {
            //trace("blocking bottom");
        }
    }

    if (g_playerX < 1)
    {
        set_screen(g_currentWorldX - 1, g_currentWorldY, false);
        g_playerX = SCREEN_WIDTH - 2;
    }
    else if (g_playerX > SCREEN_WIDTH - 2)
    {
        set_screen(g_currentWorldX + 1, g_currentWorldY, false);
        g_playerX = 2;
    }

    if (g_playerY < 1)
    {
        set_screen(g_currentWorldX, g_currentWorldY - 1, false);
        g_playerY = SCREEN_HEIGHT - 2;
    }
    else if (g_playerY > SCREEN_HEIGHT - 2)
    {
        set_screen(g_currentWorldX, g_currentWorldY + 1, false);
        g_playerY = 2;
    }
}

void start()
{
    // PALETTE[0] = 0x000000;    //  Black
    // PALETTE[1] = 0xcccccc;    //  Grey
    // PALETTE[2] = 0xff0000;    //  Red
    // PALETTE[3] = 0xffff00;    //  Yellow
    //PALETTE[0] = 0xe0f8cf; //
    //PALETTE[1] = 0x86c06c; //  GB
    //PALETTE[2] = 0x306850; //
    //PALETTE[3] = 0x071821; //
    PALETTE[0] = 0xffffff; //
    PALETTE[1] = 0xaaaaaa; //  black greys and white
    PALETTE[2] = 0x666666; //
    PALETTE[3] = 0x000000; //

    clear_screen();

    //  Saveload progress? TBD
    init_progress();

    load_game();
}

bool do_dirty_splash_screen()
{
    const int TotalDuration = 250;
    #ifdef NO_SPLASH
    static u32 g_splashFramesLeft = 0;
    #else
    static u32 g_splashFramesLeft = TotalDuration;
    #endif

    if (g_splashFramesLeft > 0)
    {
        g_splashFramesLeft--;
        
        if( g_splashFramesLeft <= 0 )
        {
            //  Reset palette
            PALETTE[0] = 0xffffff; //
            PALETTE[1] = 0xaaaaaa; //  black greys and white
            PALETTE[2] = 0x666666; //
            PALETTE[3] = 0x000000; //
            return false;
        }

        const int FadeInFrames = 30;
        const int FadeOutFrames = 60;

        float pct = 1.0f;
        if (g_splashFramesLeft > (TotalDuration - FadeInFrames))
        {
            //  Fade in
            pct = 1.0f - ((float)(g_splashFramesLeft - (TotalDuration - FadeInFrames)) / FadeInFrames);
        }
        else if (g_splashFramesLeft < FadeOutFrames)
        {
            //  Fade out
            pct = (float)(g_splashFramesLeft) / FadeOutFrames;
        }
        //pct = clampf(pct, 0.0f, 1.0f);

        u32 col1 = (u32)((float)0xff * pct);
        u32 col2 = (u32)((float)0xaa * pct);
        u32 col3 = (u32)((float)0x66 * pct);
        u32 col4 = 0;

        PALETTE[0] = col1 | col1 << 8 | col1 << 16 | col1 << 24;
        PALETTE[1] = col2 | col2 << 8 | col2 << 16 | col2 << 24;
        PALETTE[2] = col3 | col3 << 8 | col3 << 16 | col3 << 24;
        PALETTE[3] = 0x000000;
        
        //tracef("%d %d", (u32)pct, PALETTE[0]);

        *DRAW_COLORS = 0x4321;
        memset(FRAMEBUFFER, 0 | (0 << 2) | (0 << 4) | (0 << 6), 160*160/4);

        int yOffset = clamp((TotalDuration - g_splashFramesLeft) / 2, 0, 32) * 2;

        blitSub(SPRITE_Title, HALFTILE * 1, yOffset, 48, 32, 16, 0, SPRITE_TitleWidth, SPRITE_TitleFlags);
        blitSub(SPRITE_Title, HALFTILE * 7, yOffset, 64, 32, 0, 32, SPRITE_TitleWidth, SPRITE_TitleFlags);
        blitSub(SPRITE_Title, HALFTILE * 15, yOffset, 32, 32, 0, 64, SPRITE_TitleWidth, SPRITE_TitleFlags);

        if (g_splashFramesLeft < 150)
        {
            static int n = 0; n++;
            gfx_drawstrn("Presents...", 60, 94, 0x40, false, n / 2);
        }

        if( g_splashFramesLeft < 180)
        {
            static int delayFrames = 0;
            if (delayFrames > 0)
            {
                delayFrames--;
            }
            else
            {
                static int xPos = 64;
                static int yPos = 64;
                static int sparkleFrame = 0;
                static int sparkle1 = 0;
                sparkle1++;

                *DRAW_COLORS = 0x4320;
                u32 sparkleX = (u32)(2 + sparkleFrame % 2);
                u32 sparkleY = (u32)(4 + (sparkleFrame / 2));
                // tracef("sparkle %d %d", sparkleX, sparkleY);
                blitSub(SPRITE_Title, xPos, yPos, TILESIZE, TILESIZE, TILESIZE * sparkleX, TILESIZE * sparkleY, SPRITE_TitleWidth, SPRITE_TitleFlags);

                if (sparkle1 == 3)
                {
                    sparkle1 = 0;
                    sparkleFrame = (sparkleFrame + 1);
                    if (sparkleFrame == 4)
                    {
                        xPos = rand_range(8, 140);
                        yPos = rand_range(66, 80);
                        sparkleFrame = 0;
                        delayFrames = rand_range(0, 12);
                    }
                }
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

void update()
{
    if (do_dirty_splash_screen())
    {
        return;
    }

    input_update_early();
    g_uTicks++;


    static int resetCount = 0;
    if (g_gameState == INGAME && !g_bShowingDialogBG)
    {
        if (button_held(BUTTON_1) && button_held(BUTTON_2) && button_held(BUTTON_UP) && button_held(BUTTON_LEFT))
        {
            resetCount++;
            if (resetCount == 60)
            {
                trace("Resetting save...");
                resetCount = 0;
                reset_game();
                start();
            }
        }
        else
        {
            resetCount = 0;
            //if (button_held(BUTTON_1) && button_held(BUTTON_2))
            if (button_newly_pressed(BUTTON_2))
            {
                toggle_pause();
            }
        }
    }

    if(g_gameState == INGAME)
    {
        if (g_damageFramesLeft > 0)
        {
            g_damageFramesLeft--;
        }
    }

    if (g_transitionFramesLeft == 0)
    {
        //  process_interaction
        if (button_newly_pressed(BUTTON_1))
        {
            // trace("button newly pressed!");
            if (g_bShowingDialogBG)
            {
                if (g_bDialogFinished)
                {
                    on_dialog_confirm();
                }
                else
                {
                    g_bDialogSpeedup = true;
                }
            }
            else
            {
                //trace("testing for interactables!");
                //  Test for interactable
                bool bInteractableFound = false;
                for (int i = 0; i < NUM_INTERACTABLES; ++i)
                {
                    if (g_Interactables[i].type != IT_None)
                    {
                        u8 targetXTile;
                        u8 targetYTile;
                        get_tile_infront_of_player(&targetXTile, &targetYTile);
                        // tracef("tileinfront= %d %d", targetXTile, targetYTile);
                        if (g_Interactables[i].xPos == targetXTile && g_Interactables[i].yPos == targetYTile)
                        {
                            //  Trying to interact
                            on_interact(&g_Interactables[i]);
                            bInteractableFound = true;
                            break;
                        }
                    }
                }

                if (!bInteractableFound)
                {
                    start_swing_sword();
                }
            }
        }
        else
        {
            process_player_movement();
            //  Debug go faster
            if (button_held(BUTTON_2))
            {
                process_player_movement();
                process_player_movement();
                process_player_movement();
                process_player_movement();
            }    
        }
    }

    music_tick(g_Progress.musicBoxState == 1, g_Progress.musicBoxState == 1);

    update_room();

    draw_room();

    tick_interactables();

    draw_interactables();

    tick_enemies();

    draw_enemies();

    draw_player();

    tick_weapon();

    tick_vfx();

    draw_vfx();

    tick_collectables();

    draw_collectables();

    tick_pause();

    draw_pause();

    draw_statusbar();

    draw_dialog();

    input_update_late();
}
