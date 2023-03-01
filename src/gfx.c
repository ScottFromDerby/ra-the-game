#include "wasm4.h"
#include "gfx.h"
#include "tools.h"
#include "dialog.h"

#include "gfx_font6.h"
#include "gfx_font8.h"

//	NB. One larger!			   A  B  C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y    Z    a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z    0    1    2    3    4    5    6    7    8    9    .    ,    !    ?    '   
const u32 FONT_6pxOffsets[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 34, 38, 42, 45, 51, 56, 60, 64, 68, 72, 76, 80, 84, 88, 94, 98, 102, 106, 110, 114, 118, 122, 126, 130, 134, 138, 140, 143, 147, 150, 156, 160, 164, 168, 172, 176, 180, 183, 187, 191, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233, 237, 241, 245, 249, 251, 254, 256, 256, 256};
const u32 FONT_8pxOffsets[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 140, 145, 150, 155, 160, 165, 169, 174, 179, 182, 185, 189, 191, 197, 202, 207, 212, 217, 221, 225, 230, 235, 241, 247, 253, 258, 263, 267, 271, 275, 279, 283, 287, 291, 295, 299, 303, 305, 308, 310, 314, 317};

const u32* FONT_CurrentOffsets = FONT_8pxOffsets;

void gfx_charlenpx(char which, u32 *offset, u32 *offsetSize)
{
	if (which >= 'A' && which <= 'Z')
	{
		*offset = FONT_CurrentOffsets[which - 'A'];
		*offsetSize = FONT_CurrentOffsets[which - 'A' + 1] - *offset;
	}
	else if (which >= 'a' && which <= 'z')
	{
		*offset = FONT_CurrentOffsets[which - 'a' + 26];
		*offsetSize = FONT_CurrentOffsets[which - 'a' + 26 + 1] - *offset;
	}
	else if (which >= '0' && which <= '9')
	{
		*offset = FONT_CurrentOffsets[which - '0' + 26 + 26];
		*offsetSize = FONT_CurrentOffsets[which - '0' + 26 + 26 + 1] - *offset;
	}
	else if (which == '.')
	{
		*offset = FONT_CurrentOffsets[26 + 26 + 10 + 0];
		*offsetSize = FONT_CurrentOffsets[26 + 26 + 10 + 1 + 0] - *offset;
	}
	else if (which == ',')
	{
		*offset = FONT_CurrentOffsets[26 + 26 + 10 + 1];
		*offsetSize = FONT_CurrentOffsets[26 + 26 + 10 + 1 + 1] - *offset;
	}
	else if (which == '!')
	{
		*offset = FONT_CurrentOffsets[26 + 26 + 10 + 2];
		*offsetSize = FONT_CurrentOffsets[26 + 26 + 10 + 1 + 2] - *offset;
	}
	else if (which == '?')
	{
		*offset = FONT_CurrentOffsets[26 + 26 + 10 + 3];
		*offsetSize = FONT_CurrentOffsets[26 + 26 + 10 + 1 + 3] - *offset;
	}
	else if (which == '\'')
	{
		*offset = FONT_CurrentOffsets[26 + 26 + 10 + 4];
		*offsetSize = FONT_CurrentOffsets[26 + 26 + 10 + 1 + 4] - *offset;
	}
	else if (which == ' ')
	{
		*offset = 0;
		*offsetSize = 2;
	}
	else
	{
		*offset = 0;
		*offsetSize = 0;
		tracef("Unknown drawchar: %c", which);
	}
}

u32 gfx_strlenpx(const char *str)
{
	u32 width = 0;
	while (*str != '\0')
	{
		u32 offset;
		u32 offsetSize;
		gfx_charlenpx(*str, &offset, &offsetSize);
		width += offsetSize;
		str++;
	}
	return width;
}

//	Returns width of char drawn
u32 gfx_drawchar(char which, int x, int y, u16 drawcolors)
{
	u32 offset = 0;
	u32 offsetSize = 0;

	if (which == ' ')
	{
		return 2;
	}

	gfx_charlenpx(which, &offset, &offsetSize);

	*DRAW_COLORS = drawcolors;

	//blitSub(FONT_6px, x, y, offsetSize, FONT_6pxHeight, offset, 0, FONT_6pxWidth, FONT_6pxFlags);

	blitSub(FONT_8px, x, y, offsetSize, FONT_8pxHeight, offset, 0, FONT_8pxWidth, FONT_8pxFlags);
	return offsetSize;
}

void gfx_drawstrn(const char* str, int x, int y, u16 drawcolors, int numChars, int targetWidthPx)
{
	const char* startStr = str;
	int startX = x;

	while (*str != '\0' && numChars > 0)
	{
		if (*str == '#')
		{
			str++;
			drawcolors = DIALOG_ALT;
		}
		else if (*str == '~')
		{
			str++;
			drawcolors = DIALOG_DEFAULT;
		}
		else
		{
			x += gfx_drawchar(*str, x, y, drawcolors);
			str++;
			numChars--;

			if( x > targetWidthPx - startX )
			{
				y += 8;
				x = startX;
				//	Also wind back to last space NB bit dangerous
				while (*str != ' ' && str != startStr)
				{
					str--;
				}
				str++;
			}
		}
	}
}

void gfx_drawstr(const char *str, int x, int y, u16 drawcolors, bool rightalign)
{
	if (rightalign)
	{
		x -= gfx_strlenpx(str);
	}

	while (*str != '\0')
	{
		x += gfx_drawchar(*str, x, y, drawcolors);
		str++;
	}
}

void gfx_drawval(int val, int x, int y, u16 drawcolors)
{
	char buffer[256];
	tostr(buffer, val);
	gfx_drawstr(buffer, x, y, drawcolors, false);
}

void gfx_drawval_rightalign(int val, int x, int y, u16 drawcolors)
{
	char buffer[256];
	tostr(buffer, val);
	gfx_drawstr(buffer, x, y, drawcolors, true);
}

void gfx_setpixel(int x, int y, int paletteColor)
{
	if (x > SCREEN_SIZE || y > SCREEN_SIZE)
	{
		return;
	}

	// uint8_t& pixel = FRAMEBUFFER[y*40 + x / 4];

	// The byte index into the framebuffer that contains (x, y)
	int idx = (y * 160 + x) >> 2;

	// Calculate the bits within the byte that corresponds to our position
	int shift = (x & 0b11) << 1;
	int mask = 0b11 << shift;

	int color = paletteColor;

	// Write to the framebuffer
	FRAMEBUFFER[idx] = (u8)((color << shift) | (FRAMEBUFFER[idx] & ~mask));
}