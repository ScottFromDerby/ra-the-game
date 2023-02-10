#include "wasm4.h"

#include "gfx.h"
#include "music.h"
#include "tools.h"
#include "progress.h"
#include "interactables.h"
#include "animtiles.h"
#include "dialog.h"

#include "mapdata.h"

//  Assets
#include "gfx_animtiles.h"
#include "gfx_player.h"
#include "gfx_playerdebug.h"
#include "gfx_hud.h"
#include "gfx_npcs.h"
#include "gfx_overworld.h"

//  Globals
enum
{
    HALFTILE = 8,
    TILESIZE = 16,
    NUM_TILES_WIDTH = 10,
    NUM_TILES_HEIGHT = 9,
    SCREEN_WIDTH = TILESIZE * NUM_TILES_WIDTH,
    SCREEN_HEIGHT = TILESIZE * NUM_TILES_HEIGHT,
};

enum GameState
{
    INGAME,
    GAMEOVER
} g_gameState = INGAME;

enum Direction
{
    Left,
    Right,
    Up,
    Down,
} g_currentFacing = Down;

u32 g_uTicks = 0;
u32 g_uTicksInGame = UINT32_MAX;
u32 g_uHighScore = 0;

u32 g_upHeldFrames = 0;
u32 g_downHeldFrames = 0;
u32 g_leftHeldFrames = 0;
u32 g_rightHeldFrames = 0;

u8 g_playerX = (SCREEN_SIZE / 2) - (SPRITE_PlayerDebugHeight / 2);
u8 g_playerY = (SCREEN_SIZE / 2) - (SPRITE_PlayerDebugHeight / 2);

struct ScreenMeta* g_currentScreen = 0;
struct ScreenMeta* g_transitionFromScreen = 0;
u8 g_currentWorldX = 2;
u8 g_currentWorldY = 2;
int g_transitionFramesLeft = 0;
enum Direction g_transitionDirection = Left;

bool g_bButton1Released = false;

void get_tile_from_point(u8 x, u8 y, u8 *xTile, u8 *yTile)
{
    *xTile = x / TILESIZE;
    *yTile = y / TILESIZE;
}

MetaTile get_meta_tile(uint8_t x, uint8_t y)
{
    if (x >= NUM_TILES_WIDTH || y >= NUM_TILES_HEIGHT)
    {
        return Empt;
    }
    return g_currentScreen->screen_metatiles[x + y * NUM_TILES_WIDTH];
}

MetaTile get_meta_tile_transition(uint8_t x, uint8_t y)
{
    return g_transitionFromScreen->screen_metatiles[x + y * 10];
}

MetaTile get_metatile_at_point(u8 x, u8 y)
{
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
    {
        return Empt;
    }
    return get_meta_tile(x / TILESIZE, y / TILESIZE);
}

void get_tile_infront_of_player(u8* xTileOut, u8* yTileOut)
{
    get_tile_from_point(g_playerX, g_playerY, xTileOut, yTileOut);
    switch (g_currentFacing)
    {
        case Up:
            if ((*yTileOut) > 0)
            {
                (*yTileOut)--;
            }
            return;
        case Down:
            if ((*yTileOut) < NUM_TILES_HEIGHT)
            {
                (*yTileOut)++;
            }
            return;
        case Left:
            if ((*xTileOut) > 0)
            {
                (*xTileOut)--;
            }
            return;
        case Right:
            if ((*xTileOut) < NUM_TILES_WIDTH)
            {
                (*xTileOut)++;
            }
            return;
    }
}

void draw_animtile(int x, int y, u32 tile, u32 flags, int xOffs, int yOffs)
{
    blitSub(SPRITE_AnimTiles, HALFTILE * x + xOffs, HALFTILE * y + yOffs, HALFTILE, HALFTILE, (tile % 0x04) * HALFTILE, (tile / 0x04) * HALFTILE, SPRITE_AnimTilesWidth, SPRITE_AnimTilesFlags | flags);
}

void draw_halftile(int x, int y, u32 tile, u32 flags, int xOffs, int yOffs)
{
    blitSub(SPRITE_Overworld, HALFTILE * x + xOffs, HALFTILE * y + yOffs, HALFTILE, HALFTILE, (tile % 0x10) * HALFTILE, (tile / 0x10) * HALFTILE, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

void draw_metatile(int x, int y, MetaTile tile, u32 flags, int xOffs, int yOffs)
{
    uint8_t TL = 0;
    uint8_t TR = 0;
    uint8_t BL = 0;
    uint8_t BR = 0;
    u32 tile_flags = get_meta_tile_info(tile, &TL, &TR, &BL, &BR);
    draw_halftile(x * 2, y * 2, (u32)TL, tile_flags | flags, xOffs, yOffs);
    draw_halftile(x * 2 + 1, y * 2, (u32)TR, tile_flags | flags, xOffs, yOffs);
    draw_halftile(x * 2, y * 2 + 1, (u32)BL, tile_flags | flags, xOffs, yOffs);
    draw_halftile(x * 2 + 1, y * 2 + 1, (u32)BR, tile_flags | flags, xOffs, yOffs);
}

void on_start_screen()
{
    switch (g_currentWorldX | (g_currentWorldY << 4))   //  NB. this = 0x[X][Y] for world pos
    {
        case 0x20:
        trace("left2");
        break;
        case 0x21:
        trace("left");
        add_interactable(IT_AnotherNPC, 4, 4, true);
        break;
        case 0x22:
        trace("start");
        add_anim_tile(ATT_Flower, 16, 12, 0);
        add_anim_tile(ATT_Flower, 17, 13, 2);
        add_anim_tile(ATT_Flower, 4, 10, 0);
        add_anim_tile(ATT_Flower, 5, 11, 2);
        add_anim_tile(ATT_Flower, 12, 4, 0);
        add_anim_tile(ATT_Flower, 13, 5, 2);
        add_interactable(IT_StartTestNPC, 7, 2, true);
        break;
    }
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
        // trace("Setting initial screen");
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

void draw_player()
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

void draw_interactables()
{
    for (int i = 0; i < NUM_INTERACTABLES; ++i)
    {
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
        }
    }
}

void draw_dialog()
{
    if (!g_bShowingDialogBG)
    {
        return;
    }

    //  TBD: Scrolling text!

    *DRAW_COLORS = 0x1121;

    for (int i = 0; i < 10; ++i)
    {
        blitSub(SPRITE_Hud, TILESIZE * i, TILESIZE * 7, 16, 16, TILESIZE * 1, 0, SPRITE_HudWidth, SPRITE_HudFlags);
        blitSub(SPRITE_Hud, TILESIZE * i, TILESIZE * 8, 16, 16, TILESIZE * 1, 0, SPRITE_HudWidth, SPRITE_HudFlags);
        blitSub(SPRITE_Hud, TILESIZE * i, TILESIZE * 9, 16, 16, TILESIZE * 1, 0, SPRITE_HudWidth, SPRITE_HudFlags);
    }

    //  TL
    blitSub(SPRITE_Hud, 0, TILESIZE * 7, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags);
    //  TR
    blitSub(SPRITE_Hud, TILESIZE * 9, TILESIZE * 7, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X);
    //  BL
    blitSub(SPRITE_Hud, 0, TILESIZE * 9, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_Y);
    //  BR
    blitSub(SPRITE_Hud, TILESIZE * 9, TILESIZE * 9, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X | BLIT_FLIP_Y);

    // gfx_drawstr(g_dialogContent, 4, TILESIZE*7 + 4,0x1112, false);
    // gfx_drawstr("Or maybe not... Pack the whole plot into this", 4, TILESIZE*7 + 12,0x1112, false);
    ////gfx_drawstr("ABCDEF.GHIJKL.MNOPQR.STUVWX.YZ", 0, TILESIZE*7 + 12,0x1112, false);
    // gfx_drawstr("tiny bit of dialog box... could work... heh", 4, TILESIZE*7 + 20,0x1112, false);
    ////gfx_drawstr("ab.cd.ef.gh.ij.kl.mn.op.qr.st.uv.wx.yz", 0, TILESIZE*7 + 20,0x1112, false);
    // gfx_drawstr("Hi there RA!", 4, TILESIZE*7 + 28,0x1112, false);
    // gfx_drawstr("Hey Cheevo its Tele, lets go adventuring!", 4, TILESIZE*7 + 36,0x1112, false);

    // gfx_drawstr("A very bad quack might jinx zippy ", 8, TILESIZE*7 + 7, 0x0032, false);
    // gfx_drawstr("fowls.  Can you tell me if", 8, TILESIZE*7 + 19, 0x0042, false);
    // gfx_drawstr("you think this font is ok? Cost 5G", 8, TILESIZE*7 + 31, 0x0012, false);

    gfx_drawstr(g_dialogContentLine1, 8, TILESIZE * 7 + 7, 0x0032, false);
    gfx_drawstr(g_dialogContentLine2, 8, TILESIZE * 7 + 19, 0x0042, false);
    gfx_drawstr(g_dialogContentLine3, 8, TILESIZE * 7 + 31, 0x0012, false);

    *DRAW_COLORS = 0x0021;
    blitSub(SPRITE_Hud, TILESIZE * 9, TILESIZE * 9, TILESIZE, TILESIZE, (g_uTicksInGame % 30 > 5) ? TILESIZE * 2 : TILESIZE * 3, 0, SPRITE_HudWidth, SPRITE_HudFlags);
}

void draw_statusbar()
{
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

    tostr(buffer, (int)g_uTicksInGame % 60);
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
        //  If my left side is allowed near my top and bottom to move onto the
        //   tile to the left of me, do so
        if (can_move_onto_tile(get_metatile_at_point(g_playerX - 4 - 1, g_playerY - 0)) &&
            can_move_onto_tile(get_metatile_at_point(g_playerX - 4 - 1, g_playerY + 6)))
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
        //  If my right side is allowed near the top and bottom to move onto the
        //   tile to the left of me, do so
        if (can_move_onto_tile(get_metatile_at_point(g_playerX + 4 + 1, g_playerY - 0)) &&
            can_move_onto_tile(get_metatile_at_point(g_playerX + 4 + 1, g_playerY + 6)))
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
        //  If my top side is allowed near my top left and right to move onto the
        //   tile above me, do so
        if (can_move_onto_tile(get_metatile_at_point(g_playerX - 4, g_playerY - 0 - 1)) &&
            can_move_onto_tile(get_metatile_at_point(g_playerX + 4, g_playerY - 0 - 1)))
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
        //  If my bottom side is allowed near the bottom left and right to move onto the
        //   tile below me, do so
        if (can_move_onto_tile(get_metatile_at_point(g_playerX - 4, g_playerY + 6 + 1)) &&
            can_move_onto_tile(get_metatile_at_point(g_playerX + 4, g_playerY + 6 + 1)))
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

    // const int HALF_PLY = SPRITE_PlayerDebugHeight / 2;
    // g_playerX = clampu8(g_playerX, 1, SCREEN_SIZE - TILESIZE - 1);
    // g_playerY = clampu8(g_playerY, 1, SCREEN_SIZE - TILESIZE - 1);
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
}

void update()
{
    g_uTicks++;
    if (g_gameState == INGAME)
    {
        g_uTicksInGame++;
    }

    process_player_movement();

    //  process_interaction
    u8 gamepad = *GAMEPAD1;
    if ((gamepad & BUTTON_1) && g_bButton1Released)
    {
        if (g_bShowingDialogBG)
        {
            on_dialog_confirm();
        }
        else
        {
            //  Test for interactable
            for( int i = 0; i < NUM_INTERACTABLES; ++i )
            {
                if (g_Interactables[i].type != IT_None)
                {
                    u8 targetXTile;
                    u8 targetYTile;
                    get_tile_infront_of_player(&targetXTile, &targetYTile);
                    //tracef("tileinfront= %d %d", targetXTile, targetYTile);
                    if( g_Interactables[i].xPos == targetXTile && g_Interactables[i].yPos == targetYTile )
                    {
                        //  Trying to interact
                        on_interact(&g_Interactables[i]);
                        break;
                    }
                }
            }
        }
        
        //tracef("btn pressed");
        g_bButton1Released = false;
    }
    else if( (gamepad & BUTTON_1) == 0)
    {
        if( g_bButton1Released == false)
        {
            //tracef("btn released");
            g_bButton1Released = true;
        }
    }

    // music_tick(g_gameState == INGAME);

    update_map();

    draw_map();

    tick_interactables();

    draw_interactables();

    draw_player();

    draw_statusbar();

    draw_dialog();
}
