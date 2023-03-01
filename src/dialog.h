#pragma once
#include "wasm4.h"

void show_dialog(const uint16_t* pDialogData);

//  Either shows a new dialog or allows itself to be simply closed.
void toggle_dialog(const uint16_t* pDialogData);

void close_dialog();

void draw_dialog();

extern bool g_bShowingDialogBG;
extern bool g_bDialogFinished;
extern bool g_bDialogSpeedup;
extern char g_dialogContent[512];
extern int g_dialogTicks;

enum
{
    DIALOG_DEFAULT = 0x0040,
    DIALOG_ALT = 0x0030,
};