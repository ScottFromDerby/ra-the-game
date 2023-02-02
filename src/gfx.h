#pragma once
#include <stdio.h>

u32 gfx_drawchar(char which, int x, int y, u16 drawcolors);
void gfx_drawstr(const char* str, int x, int y, u16 drawcolors);
void gfx_drawval(u32 val, int x, int y, u16 drawcolors);
void gfx_setpixel(int x, int y, int paletteColor);