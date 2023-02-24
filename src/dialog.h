#pragma once
#include "wasm4.h"

void show_dialog(const char* line1, const char* line2, const char* line3);

//  Either shows a new dialog or allows itself to be simply closed.
void toggle_dialog(const char* line1, const char* line2, const char* line3);

void close_dialog();

void draw_dialog();

extern bool g_bShowingDialogBG;
extern bool g_bDialogFinished;
extern bool g_bDialogSpeedup;
extern char g_dialogContentLine1[64];
extern char g_dialogContentLine2[64];
extern char g_dialogContentLine3[64];
extern int g_dialogTicks;

enum
{
    DIALOG_DEFAULT = 0x0040,
    DIALOG_ALT = 0x0030,
};