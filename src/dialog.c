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
