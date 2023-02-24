#include "wasm4.h"
#include "dialog.h"

#include "gfx.h"
#include "tools.h"
#include "gfx_hud.h"

bool g_bShowingDialogBG = false;
bool g_bDialogFinished = false;
bool g_bDialogSpeedup = false;

char g_dialogContentLine1[64];
char g_dialogContentLine2[64];
char g_dialogContentLine3[64];
int g_dialogTicks = 0;

//  nonglobal
int dialogNumChars1 = 0;
int dialogNumChars2 = 0;
int dialogNumChars3 = 0;

int strlendlg(char* str)
{
    //  strlen which ignores colcodes
    int len = 0;
    while (*str != '\0')
    {
        if (*str != '#' && *str != '~')
        {
            len++;
        }
        str++;
    }
    return len;
}

void show_dialog(const char* line1, const char* line2, const char* line3)
{
    strcpy(g_dialogContentLine1, line1);
    strcpy(g_dialogContentLine2, line2);
    strcpy(g_dialogContentLine3, line3);

    g_bShowingDialogBG = true;
    g_dialogTicks = 0;
    g_bDialogFinished = false;
    g_bDialogSpeedup = false;

    dialogNumChars1 = strlendlg(g_dialogContentLine1);
    dialogNumChars2 = strlendlg(g_dialogContentLine2);
    dialogNumChars3 = strlendlg(g_dialogContentLine3);
}

void close_dialog()
{
    g_bShowingDialogBG = false;
}

//  Either shows a new dialog or allows itself to be simply closed.
void toggle_dialog(const char* line1, const char* line2, const char* line3)
{
    if (!g_bShowingDialogBG)
    {
        show_dialog(line1, line2, line3);
    }
    else
    {
        g_bShowingDialogBG = false;
    }
}

void draw_dialog()
{
    if (!g_bShowingDialogBG)
    {
        return;
    }

    //  TBD: Scrolling text!

    *DRAW_COLORS = 0x4321;

    for (int i = 0; i < 10; ++i)
    {
        blitSub(SPRITE_Hud, TILESIZE * i, TILESIZE * 6, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags);
        blitSub(SPRITE_Hud, TILESIZE * i, TILESIZE * 7, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags);
        blitSub(SPRITE_Hud, TILESIZE * i, TILESIZE * 8, TILESIZE, TILESIZE, TILESIZE * 0, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags);
    }

    //  TL
    blitSub(SPRITE_Hud, TILESIZE * 0, TILESIZE * 6, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags);
    //  TR
    blitSub(SPRITE_Hud, TILESIZE * 9, TILESIZE * 6, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X);
    //  BL
    blitSub(SPRITE_Hud, TILESIZE * 0, TILESIZE * 8, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_Y);
    //  BR
    blitSub(SPRITE_Hud, TILESIZE * 9, TILESIZE * 8, TILESIZE, TILESIZE, TILESIZE * 1, TILESIZE * 1, SPRITE_HudWidth, SPRITE_HudFlags | BLIT_FLIP_X | BLIT_FLIP_Y);

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

    int charsToDraw = g_dialogTicks / 2;
    gfx_drawstrn(g_dialogContentLine1, HALFTILE - 1, TILESIZE * 6 + 7, DIALOG_DEFAULT, false, charsToDraw);
    charsToDraw -= dialogNumChars1;
    gfx_drawstrn(g_dialogContentLine2, HALFTILE - 1, TILESIZE * 7 + 4, DIALOG_DEFAULT, false, charsToDraw);
    charsToDraw -= dialogNumChars2;
    gfx_drawstrn(g_dialogContentLine3, HALFTILE - 1, TILESIZE * 8 + 1, DIALOG_DEFAULT, false, charsToDraw);
    charsToDraw -= dialogNumChars3;

    g_bDialogFinished = (charsToDraw >= 0);

    //  Press X 
    if( g_bDialogFinished || !g_bDialogSpeedup)
    {
        *DRAW_COLORS = 0x4000;
        blitSub(SPRITE_Hud, TILESIZE * 9, TILESIZE * 8, TILESIZE, TILESIZE, (g_uTicks % 30 > 5) ? TILESIZE * 2 : TILESIZE * 3, TILESIZE * 0, SPRITE_HudWidth, SPRITE_HudFlags);
    }

    g_dialogTicks++;
    if (g_bDialogSpeedup)
    {
        g_dialogTicks++;
    }
}
