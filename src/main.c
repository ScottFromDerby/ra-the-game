#include "wasm4.h"

#include "gfx.h"
#include "music.h"
#include "tools.h"

//  Assets
#include "gfx_player.h"
#include "gfx_playerdebug.h"
#include "gfx_hud.h"
#include "gfx_npcs.h"
#include "gfx_overworld.h"

// Chainsaw
#define SPRITE_ChainsawWidth 128
#define SPRITE_ChainsawHeight 16
#define SPRITE_ChainsawFlags BLIT_2BPP
const uint8_t SPRITE_Chainsaw[512] = {0x14, 0x00, 0x00, 0x00, 0x00, 0x05, 0x50, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x80, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x0a, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x05, 0x50, 0x00, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x10, 0x00, 0xaa, 0xa0, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x00, 0x00, 0x00, 0xa2, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x55, 0x40, 0x00, 0x00, 0x00, 0x15, 0x50, 0x00, 0x00, 0x40, 0x05, 0x55, 0x00, 0x01, 0x00, 0x00, 0xaa, 0xa0, 0x00, 0x00, 0x00, 0x82, 0xa8, 0x00, 0x00, 0x00, 0x82, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x55, 0x50, 0x00, 0x00, 0x00, 0x55, 0x50, 0x00, 0x00, 0x05, 0x15, 0x54, 0x00, 0x01, 0x04, 0x00, 0xaa, 0xa8, 0x00, 0x40, 0x00, 0x8a, 0xa8, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x15, 0x54, 0x00, 0x00, 0x00, 0x05, 0x50, 0x00, 0x01, 0x00, 0x55, 0x50, 0xa0, 0x00, 0x05, 0x10, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x2a, 0xa0, 0x00, 0x00, 0x02, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0xa2, 0x05, 0x55, 0x00, 0x00, 0x01, 0x15, 0x50, 0x00, 0x00, 0x41, 0x55, 0x40, 0xaa, 0x24, 0x10, 0x04, 0x82, 0xa9, 0x00, 0x10, 0x00, 0x26, 0x98, 0x00, 0x00, 0x02, 0x6a, 0xa8, 0x00, 0x00, 0x2a, 0x02, 0x05, 0x55, 0x40, 0x00, 0x11, 0x55, 0x50, 0x00, 0x00, 0x05, 0x55, 0x00, 0xaa, 0x95, 0x55, 0x55, 0x22, 0xa9, 0x40, 0x50, 0x00, 0x29, 0x54, 0x00, 0x00, 0x01, 0x6a, 0x80, 0x55, 0x55, 0x66, 0x8a, 0x14, 0x55, 0x5a, 0x00, 0x00, 0x05, 0x50, 0x00, 0x00, 0x15, 0x54, 0x00, 0xaa, 0xa5, 0x55, 0x55, 0x2a, 0x95, 0x50, 0x40, 0x00, 0x05, 0x50, 0x00, 0x00, 0x05, 0x56, 0x00, 0x55, 0x55, 0x5a, 0xaa, 0x00, 0x55, 0x56, 0xa8, 0x40, 0x05, 0x50, 0x00, 0x00, 0x95, 0x50, 0x00, 0xaa, 0xa5, 0x55, 0x55, 0x00, 0xa5, 0x55, 0x01, 0x00, 0x05, 0x50, 0x00, 0x00, 0x15, 0x50, 0x00, 0x55, 0x55, 0x5a, 0xaa, 0x01, 0x45, 0x6a, 0x88, 0x00, 0x15, 0x68, 0x00, 0x02, 0xa9, 0x40, 0x00, 0xa2, 0x99, 0x55, 0x55, 0x00, 0x01, 0x55, 0x05, 0x00, 0x05, 0x55, 0x40, 0x00, 0x55, 0x44, 0x00, 0x55, 0x55, 0x56, 0xaa, 0x01, 0x01, 0x6a, 0x82, 0x00, 0x26, 0x98, 0x00, 0x2a, 0xa9, 0x80, 0x00, 0x80, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x55, 0x50, 0x00, 0x05, 0x54, 0x40, 0x01, 0x55, 0x01, 0x00, 0x10, 0x04, 0x18, 0xaa, 0x04, 0x00, 0xaa, 0xaa, 0x00, 0x0a, 0xa8, 0x00, 0xaa, 0xaa, 0x80, 0x00, 0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x50, 0x00, 0x05, 0x50, 0x00, 0x05, 0x54, 0x10, 0x00, 0x04, 0x50, 0x00, 0x0a, 0x00, 0x00, 0x2a, 0xaa, 0x00, 0x2a, 0xa2, 0x00, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x55, 0x00, 0x05, 0x55, 0x00, 0x15, 0x54, 0x05, 0x10, 0x00, 0x10, 0x40, 0x00, 0x01, 0x00, 0x0a, 0xaa, 0x00, 0x2a, 0x82, 0x00, 0xaa, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x55, 0x00, 0x05, 0x54, 0x00, 0x55, 0x45, 0x41, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x00, 0xaa, 0xa0, 0x00, 0xaa, 0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x05, 0x50, 0x00, 0x15, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0xa8, 0x00, 0xaa, 0xaa, 0x00, 0x2a, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x05, 0x50, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//  Globals

enum
{
    HALFTILE = 8,
    TILESIZE = 16,
    //NUM_ENEMIES = 32,
    //NUM_BLOODSPLATTER_PIXELS = 32
};

enum GameState
{
    INGAME,
    GAMEOVER
} g_gameState = INGAME;

enum FacingDirection
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    Unknown
} g_currentFacing = SOUTH;

u32 g_uTicks = 0;
u32 g_uTicksInGame = UINT32_MAX;
u32 g_uHighScore = 0;

u32 g_upHeldFrames = 0;
u32 g_downHeldFrames = 0;
u32 g_leftHeldFrames = 0;
u32 g_rightHeldFrames = 0;

int g_playerX = (SCREEN_SIZE / 2) - (SPRITE_PlayerDebugHeight / 2);
int g_playerY = (SCREEN_SIZE / 2) - (SPRITE_PlayerDebugHeight / 2);

int g_npc1X = TILESIZE*6;
int g_npc1Y = TILESIZE*2;

u32 g_ignoreButtonInputsDelay = 0;

bool g_bShowingDialogBG = false;
char g_dialogContent[64];

void draw_halftile(int x, int y, u32 tile, u32 flags)
{
    blitSub(SPRITE_Overworld, HALFTILE*x, HALFTILE*y, HALFTILE, HALFTILE, (tile%16)*HALFTILE, (tile/16)*HALFTILE, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

void draw_tile(int x, int y, u32 tile, u32 flags)
{
    blitSub(SPRITE_Overworld, TILESIZE*x, TILESIZE*y, TILESIZE, TILESIZE, (tile%8)*TILESIZE, (tile/8)*TILESIZE, SPRITE_OverworldWidth, SPRITE_OverworldFlags | flags);
}

void draw_map()
{
    *DRAW_COLORS = 0x4321;
    draw_tile(1, 1, 0, 0);
    draw_tile(2, 1, 1, 0);
    draw_tile(1, 2, 2, 0);
    draw_tile(2, 2, 3, 0);

    draw_halftile(8, 7, 58, 0);
    draw_halftile(12, 8, 58, 0);
    draw_halftile(13, 14, 58, 0);
    draw_halftile(7, 3, 58, 0);
    draw_halftile(1, 8, 58, 0);
}

void draw_player()
{
    u32 spriteSheetOffsetX = 0;
    u32 spriteSheetOffsetY = 0;
    u32 spriteSheetRenderFlags = 0;
    switch(g_currentFacing)
    {
case NORTH:
    spriteSheetOffsetX = 16;
    spriteSheetOffsetY = 0;
    spriteSheetRenderFlags = (g_upHeldFrames % 16 > 8) ? BLIT_FLIP_X : 0;
break;
case SOUTH:
    spriteSheetOffsetX = 0;
    spriteSheetOffsetY = 0;
    spriteSheetRenderFlags = (g_downHeldFrames % 16 > 8) ? BLIT_FLIP_X : 0;
break;
case EAST:
    spriteSheetOffsetX = (g_rightHeldFrames % 16 > 8) ? 32 : 48;
    spriteSheetOffsetY = 0;
    spriteSheetRenderFlags = BLIT_FLIP_X;
break;
case WEST:
    spriteSheetOffsetX = (g_leftHeldFrames % 16 > 8) ? 32 : 48;
    spriteSheetOffsetY = 0;
    spriteSheetRenderFlags = 0;
break;
default:
break;
    }

    *DRAW_COLORS = 0x0321;
    blitSub(SPRITE_Player, g_playerX, g_playerY, TILESIZE, TILESIZE, spriteSheetOffsetX, spriteSheetOffsetY, SPRITE_PlayerWidth, SPRITE_PlayerFlags | spriteSheetRenderFlags);
}

void draw_npcs()
{
    *DRAW_COLORS = 0x1240;
    blitSub(SPRITE_NPCs, g_npc1X, g_npc1Y, TILESIZE, TILESIZE, 0, TILESIZE * 4, SPRITE_NPCsWidth, SPRITE_NPCsFlags | ((g_uTicks % 40 > 20) ? 0 : BLIT_FLIP_X));
}

void draw_dialog()
{
    if (g_bShowingDialogBG)
    {
        *DRAW_COLORS = 0x1121;

        for(int i = 0; i < 10; ++i)
        {
            blitSub(SPRITE_Hud, TILESIZE*i, TILESIZE*7, 16, 16, TILESIZE*1, 0, SPRITE_HudWidth, SPRITE_HudFlags);
            blitSub(SPRITE_Hud, TILESIZE*i, TILESIZE*8, 16, 16, TILESIZE*1, 0, SPRITE_HudWidth, SPRITE_HudFlags);
            blitSub(SPRITE_Hud, TILESIZE*i, TILESIZE*9, 16, 16, TILESIZE*1, 0, SPRITE_HudWidth, SPRITE_HudFlags);
        }

        //  TL
        blitSub(SPRITE_Hud, 0, TILESIZE*7, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags);
        //  TR
        blitSub(SPRITE_Hud, TILESIZE*9, TILESIZE*7, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X);
        //  BL
        blitSub(SPRITE_Hud, 0, TILESIZE*9, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_Y);
        //  BR
        blitSub(SPRITE_Hud, TILESIZE*9, TILESIZE*9, 16, 16, 0, 0, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X | BLIT_FLIP_Y);

        //gfx_drawstr(g_dialogContent, 4, TILESIZE*7 + 4,0x1112, false);
        //gfx_drawstr("Or maybe not... Pack the whole plot into this", 4, TILESIZE*7 + 12,0x1112, false);
        ////gfx_drawstr("ABCDEF.GHIJKL.MNOPQR.STUVWX.YZ", 0, TILESIZE*7 + 12,0x1112, false);
        //gfx_drawstr("tiny bit of dialog box... could work... heh", 4, TILESIZE*7 + 20,0x1112, false);
        ////gfx_drawstr("ab.cd.ef.gh.ij.kl.mn.op.qr.st.uv.wx.yz", 0, TILESIZE*7 + 20,0x1112, false);
        //gfx_drawstr("Hi there RA!", 4, TILESIZE*7 + 28,0x1112, false);
        //gfx_drawstr("Hey Cheevo its Tele, lets go adventuring!", 4, TILESIZE*7 + 36,0x1112, false);

        //gfx_drawstr("A very bad quack might jinx zippy ", 8, TILESIZE*7 + 7, 0x0032, false);
        //gfx_drawstr("fowls.  Can you tell me if", 8, TILESIZE*7 + 19, 0x0042, false);
        //gfx_drawstr("you think this font is ok? Cost 5G", 8, TILESIZE*7 + 31, 0x0012, false);
        
        gfx_drawstr("You win the game! Please leave 5strs", 8, TILESIZE*7 + 7, 0x0032, false);
        gfx_drawstr("like, subscribe and tell your frens", 8, TILESIZE*7 + 19, 0x0042, false);
        gfx_drawstr("also buy the Cheevo DLC only 1000G", 8, TILESIZE*7 + 31, 0x0012, false);

    	*DRAW_COLORS = 0x0021;
        blitSub(SPRITE_Hud, TILESIZE*9, TILESIZE*9, TILESIZE, TILESIZE, (g_uTicksInGame % 30 > 5) ? TILESIZE*2 : TILESIZE*3, 0, SPRITE_HudWidth, SPRITE_HudFlags);
    }
}

void start()
{
    //PALETTE[0] = 0x000000;  //  Black
    //PALETTE[1] = 0xcccccc;  //  Grey
    //PALETTE[2] = 0xff0000;  //  Red
    //PALETTE[3] = 0xffff00;  //  Yellow
    PALETTE[0] = 0xe0f8cf;  //  
    PALETTE[1] = 0x86c06c;  //  GB
    PALETTE[2] = 0x306850;  //  
    PALETTE[3] = 0x071821;  //  

    strcpy(g_dialogContent, "Think we gonna need a bigger font. Too tiny!");
}

void update()
{
    g_uTicks++;

    if (g_gameState == INGAME)
    {
        g_uTicksInGame++;
    }

    //  Draw score/highscore
    if (g_uTicksInGame != UINT32_MAX)
    {
        char buffer[16];
        tostr(buffer, g_uTicksInGame / 10);
        gfx_drawstr(buffer, 1, 1, 0x21, false);

        if ((g_uTicksInGame / 10) > g_uHighScore)
        {
            g_uHighScore = g_uTicksInGame / 10;
        }

        if (g_uHighScore != 0)
        {
            //	qad right-align high score
            int xOffs = SCREEN_SIZE - 4;
            if (g_uHighScore >= 1000)
            {
                xOffs = SCREEN_SIZE - 16;
            }
            else if (g_uHighScore >= 100)
            {
                xOffs = SCREEN_SIZE - 12;
            }
            else if (g_uHighScore >= 10)
            {
                xOffs = SCREEN_SIZE - 8;
            }
            gfx_drawval((int)g_uHighScore, xOffs, 1, 0x31);
        }
    }

    //  Draw grid TEST
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int drawX = 0; drawX < 16; drawX += 4)
            {
                //gfx_setpixel(i * 16 + drawX, j * 16, 0x0001);
            }
            for (int drawY = 1; drawY < 16; drawY += 4)
            {
                //gfx_setpixel(i * 16, j * 16 + drawY, 0x0002);
            }
        }
    }

    //  Process player movement
    u8 gamepad = *GAMEPAD1;

    if (g_gameState == INGAME && !g_bShowingDialogBG)
    {
        if (gamepad & BUTTON_RIGHT)
        {
            g_playerX++;
            g_leftHeldFrames = 0;
            g_rightHeldFrames++;
            if (g_upHeldFrames == 0 && g_downHeldFrames == 0)
            {
                g_currentFacing = EAST;
            }
        }
        else if (gamepad & BUTTON_LEFT)
        {
            g_playerX--;
            g_rightHeldFrames = 0;
            g_leftHeldFrames++;
            if (g_upHeldFrames == 0 && g_downHeldFrames == 0)
            {
                g_currentFacing = WEST;
            }
        }
        else
        {
            g_leftHeldFrames = 0;
            g_rightHeldFrames = 0;
        }
        if (gamepad & BUTTON_DOWN)
        {
            g_playerY++;
            g_upHeldFrames = 0;
            g_downHeldFrames++;
            if (g_leftHeldFrames == 0 && g_rightHeldFrames == 0)
            {
                g_currentFacing = SOUTH;
            }
        }
        else if (gamepad & BUTTON_UP)
        {
            g_playerY--;
            g_downHeldFrames = 0;
            g_upHeldFrames++;
            if (g_leftHeldFrames == 0 && g_rightHeldFrames == 0)
            {
                g_currentFacing = NORTH;
            }
        }
        else
        {
            g_upHeldFrames = 0;
            g_downHeldFrames = 0;
        }

        const int HALF_PLY = SPRITE_PlayerDebugHeight / 2;
        g_playerX = clamp(g_playerX, 0, SCREEN_SIZE - TILESIZE);
        g_playerY = clamp(g_playerY, 0, SCREEN_SIZE - TILESIZE);
    }

    if (g_ignoreButtonInputsDelay > 0)
    {
        g_ignoreButtonInputsDelay--;
    }
    else
    {
        if (g_playerX > g_npc1X - TILESIZE && g_playerX < g_npc1X + TILESIZE && g_playerY > g_npc1Y - TILESIZE && g_playerY < g_npc1Y + TILESIZE)
        {
            if (gamepad & BUTTON_1)
            {
                g_bShowingDialogBG = !g_bShowingDialogBG;
                g_ignoreButtonInputsDelay = 10;
            }
        }
    }

    //music_tick(g_gameState == INGAME);

    draw_map();

    draw_npcs();

    draw_player();

    draw_dialog();
}
