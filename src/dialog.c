#include "wasm4.h"
#include "dialog.h"
#include "tools.h"

bool g_bShowingDialogBG = false;
char g_dialogContentLine1[64];
char g_dialogContentLine2[64];
char g_dialogContentLine3[64];

void show_dialog(const char* line1, const char* line2, const char* line3)
{
    strcpy(g_dialogContentLine1, line1);
    strcpy(g_dialogContentLine2, line2);
    strcpy(g_dialogContentLine3, line3);

    g_bShowingDialogBG = true;
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