#include "wasm4.h"
#include "tools.h"
#include "gfx.h"

void tostr(char* buffer, int value)
{
	bool bIsNegative = false;
	u8 numDigits = 0;

	if (value < 0)
	{
		buffer[0] = '-';
		buffer++;
		value *= -1;
	}
	
	int test = value;
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

char* tostrdirty(int value)
{
	static char buffer[32];
	tostr(buffer, value);
	return buffer;
}
