#include "wasm4.h"
#include "tools.h"
#include "gfx.h"

void tostr(char *buffer, u32 value)
{
	u8 numDigits = 0;

	u32 test = value;
	while (test > 0)
	{
		test /= 10;
		numDigits++;
	}
	if (numDigits == 0)
	{
		numDigits = 1;
	}

	u8 numDigitsLeft = numDigits;
	while (numDigitsLeft > 0)
	{
		buffer[numDigitsLeft - 1] = '0' + (value % 10);
		value /= 10;
		numDigitsLeft--;
	}
	buffer[numDigits] = '\0';
}

char* tostrdirty(u32 value)
{
	static char buffer[32];
	tostr(buffer, value);
	return buffer;
}