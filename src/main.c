#include "wasm4.h"
#include "main.h"

#include "animtiles.h"
#include "animtiles.h"
#include "dialog.h"
#include "gfx.h"
#include "input.h"
#include "interactables.h"
#include "mapdata.h"
#include "music.h"
#include "player.h"
#include "progress.h"
#include "rendering.h"
#include "tools.h"

//  Assets
#include "gfx_hud.h"
#include "gfx_npcs.h"

u32 g_uTicks = 0;

u8 g_upHeldFrames = 0;
u8 g_downHeldFrames = 0;
u8 g_leftHeldFrames = 0;
u8 g_rightHeldFrames = 0;

enum Direction g_currentFacing = Down;
enum GameState g_gameState = INGAME;

u8 g_playerX = 100;
u8 g_playerY = 100;

struct ScreenMeta* g_currentScreen = 0;
struct ScreenMeta* g_transitionFromScreen = 0;
u8 g_currentWorldX = 2;
u8 g_currentWorldY = 2;
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

    //for( )

    gfx_drawstr("Inventory", HALFTILE * 4, HALFTILE * 3 + yOffset, 0x0032, false);
    gfx_drawstr("Spanner", HALFTILE * 4, HALFTILE * 4 + yOffset, 0x0032, false);
    gfx_drawstr("Flowers", HALFTILE * 4, HALFTILE * 5 + yOffset, 0x0032, false);

    *DRAW_COLORS = 0x3241;

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


}

bool is_tile_blocked_by_npc(u8 x, u8 y)
{
    for( int i = 0; i < NUM_INTERACTABLES; ++i )
    {
        if( ((g_Interactables[i].interactableFlags & INTERACTABLE_BLOCK_PLAYER) != 0) &&
            (g_Interactables[i].xPos == x) && 
            (g_Interactables[i].yPos == y))
        {
            trace("Blocked by NPC");
            return true;
        }
    }
    return false;
}

void on_start_screen()
{
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
    }

    save_game();
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
}

void set_screen(u8 x, u8 y, bool bForce)
{
    //tracef("doing set_screen %d %d %d %d", x, y, g_currentWorldX, g_currentWorldY);

    clear_screen();

    if (bForce)
    {
        g_currentScreen = get_screen(x, y);
        g_currentWorldX = x;
        g_currentWorldY = y;
        on_start_screen();
    }
    else
    {
        g_Progress.bHasVisitedOtherScreens = true;

        g_transitionFromScreen = g_currentScreen;
        g_currentScreen = get_screen(x, y);
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

void update_map()
{
    if (g_currentScreen == 0)
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

void draw_map()
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

    char buffer[16];

    // tostr(buffer, sizeof(*MainWorldMap.World[0]));
    // gfx_drawstr(buffer, 64, 152, 0x21, false);

    tostr(buffer, g_playerX);
    gfx_drawstr(buffer, 1, 152, 0x21, false);
    tostr(buffer, g_playerY);
    gfx_drawstr(buffer, 14, 152, 0x21, false);

    tostr(buffer, g_currentWorldX);
    gfx_drawstr(buffer, 27, 152, 0x31, false);
    tostr(buffer, g_currentWorldY);
    gfx_drawstr(buffer, 41, 152, 0x31, false);
    
    tostr(buffer, (int)g_gameState);
    gfx_drawstr(buffer, 57, 152, 0x31, false);

    tostr(buffer, (int)g_pauseState);
    gfx_drawstr(buffer, 67, 152, 0x31, false);

    tostr(buffer, (int)g_pauseStateFramesLeft);
    gfx_drawstr(buffer, 77, 152, 0x31, false);

    tostr(buffer, (int)g_uTicks % 60);
    gfx_drawstr(buffer, SCREEN_WIDTH, 152, 0x21, true);
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

    bool bWantsMoveRight = false;
    bool bWantsMoveLeft = false;
    bool bWantsMoveDown = false;
    bool bWantsMoveUp = false;

    //  Process player movement
    u8 gamepad = *GAMEPAD1;

    if (g_gameState == INGAME)
    {
        if (gamepad & BUTTON_RIGHT)
        {
            bWantsMoveRight = true;
            g_leftHeldFrames = 0;
            g_rightHeldFrames++;
            if (g_upHeldFrames == 0 && g_downHeldFrames == 0)
            {
                g_currentFacing = Right;
            }
        }
        else if (gamepad & BUTTON_LEFT)
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
        if (gamepad & BUTTON_DOWN)
        {
            bWantsMoveDown = true;
            g_upHeldFrames = 0;
            g_downHeldFrames++;
            if (g_leftHeldFrames == 0 && g_rightHeldFrames == 0)
            {
                g_currentFacing = Down;
            }
        }
        else if (gamepad & BUTTON_UP)
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
    PALETTE[1] = 0xaaaaaa; //  GB
    PALETTE[2] = 0x666666; //
    PALETTE[3] = 0x000000; //

    clear_screen();

    //  Saveload progress? TBD
    init_progress();

    load_game();
}

void update()
{
    input_update_early();
    g_uTicks++;

    process_player_movement();
    //  Debug go faster
    if (button_held(BUTTON_2))
    {
        process_player_movement();
        process_player_movement();
        process_player_movement();
        process_player_movement();
    }

    //  process_interaction
    if (button_newly_pressed(BUTTON_1))
    {
        //trace("button newly pressed!");
        if (g_bShowingDialogBG)
        {
            if( g_bDialogFinished)
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
                        break;
                    }
                }
            }
        }
    }

    if (g_gameState == INGAME && !g_bShowingDialogBG)
    {
        static int resetCount = 0;
        if (button_held(BUTTON_1) && button_held(BUTTON_2) && button_held(BUTTON_UP) && button_held(BUTTON_LEFT))
        {
            trace("Resetting save...");
            resetCount++;
            if (resetCount == 60)
            {
                resetCount = 0;
                reset_game();
                start();
            }
        }

        if (button_held(BUTTON_1) && button_held(BUTTON_2))
        {
            toggle_pause();
        }
    }
    
    if( g_gameState == PAUSE )
    {
        if (button_held(BUTTON_1) && button_held(BUTTON_2))
        {
            toggle_pause();
        }
    }

    music_tick(g_Progress.musicBoxState == 1, g_Progress.musicBoxState == 1);

    update_map();

    draw_map();

    tick_interactables();

    draw_interactables();

    draw_player_sprite();

    tick_pause();

    draw_pause();

    draw_statusbar();

    draw_dialog();

    input_update_late();
}
