#include "wasm4.h"
#include "dialog.h"
#include "dialog_data.h"

#include "gfx.h"
#include "tools.h"
#include "gfx_hud.h"

bool g_bShowingDialogBG = false;
bool g_bDialogFinished = false;
bool g_bDialogSpeedup = false;

char g_dialogContent[512];
int g_dialogTicks = 0;

//  nonglobal
const int DIALOG_WIDTH = 150;

int dialogNumChars = 0;

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

void show_dialog(const uint16_t* pDialogData)
{
    //tracef("show_dialog2, %d", pDialogData[0]);

    char *pDlg = &g_dialogContent[0];
    while (*pDialogData != (uint16_t)-1)
    {
        const char *nextToken = DLG_IDLOOKUP[*pDialogData];
        //tracef("nextToken, %d = '%s'", *pDialogData, nextToken);
        while (*nextToken != '\0')
        {
            *pDlg++ = *nextToken++;
        }

        //  Reinject spaces!
        *pDlg++ = ' ';
        pDialogData++;
    }
    *pDlg = '\0';

    g_bShowingDialogBG = true;
    g_dialogTicks = 0;
    g_bDialogFinished = false;
    g_bDialogSpeedup = false;

    dialogNumChars = strlendlg(g_dialogContent);
    //  NB. doesn't not include terminating \0 character!

    //  Inject a sneaky space at the end to make sure we can still wrap on the last word too!
    g_dialogContent[dialogNumChars+1] = ' ';
    g_dialogContent[dialogNumChars+2] = '\0';
    dialogNumChars++;

    //  Calculate where linebreaks are going to be needed! Inject inplace of space
    int textPxLength = 0;
    for (int i = 0; i < dialogNumChars; ++i)
    {
        u32 unused;
        u32 charSizePx;
        gfx_charlenpx(g_dialogContent[i], &unused, &charSizePx);
        textPxLength += charSizePx;
        //tracef("Adding %c, total size %d", g_dialogContent[i], textPxLength);
        if( g_dialogContent[i+1] == ' ')
        {
            //tracef("Detecting space. Are we over %d", DIALOG_WIDTH);
            if (textPxLength >= DIALOG_WIDTH)
            {
                //trace("Rewind! Going back to last known space...");
                //  Rewind back to last full word, inject a newline, then reset charSizePx
                i--;
                while (g_dialogContent[i] != ' ')
                {
                    //tracef("Not a space at %d (%c)", i, g_dialogContent[i]);
                    i--;
                }

                //tracef("OK found a space at %d, replacing with a newline", i);
                g_dialogContent[i] = '\n';

                //trace("Dialog is now:");
                //tracef("[%s]", g_dialogContent);
                textPxLength = 0;
            }
        }
        
    }
}

void close_dialog()
{
    g_bShowingDialogBG = false;
}

//  Either shows a new dialog or allows itself to be simply closed.
void toggle_dialog(const uint16_t* pDialogData)
{
    if (!g_bShowingDialogBG)
    {
        show_dialog(pDialogData);
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
    gfx_drawstrn(g_dialogContent, HALFTILE - 1, TILESIZE * 6 + 7, DIALOG_DEFAULT, false, charsToDraw);
    charsToDraw -= dialogNumChars;
    //gfx_drawstrn(g_dialogContentLine2, HALFTILE - 1, TILESIZE * 7 + 4, DIALOG_DEFAULT, false, charsToDraw);
    //charsToDraw -= dialogNumChars2;
    //gfx_drawstrn(g_dialogContentLine3, HALFTILE - 1, TILESIZE * 8 + 1, DIALOG_DEFAULT, false, charsToDraw);
    //charsToDraw -= dialogNumChars3;

    g_bDialogFinished = (charsToDraw >= 0);

    //  Press X
    if (g_bDialogFinished || !g_bDialogSpeedup)
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
