// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <math.h>
#include <stdio.h>

#include "Font.h"

void usage();

int main(int _iArgC, char* _szArgV[])
{
	// Ensure there are three command line parameters plus the .exe filename
	if (_iArgC != 4)
	{
		usage();
	}

	Font*	pFont	= Font::create();

	if (NULL == pFont)
	{
		printf("Unable to create Font interface\n");

		return	1;
	}

	if (false == pFont->load(_szArgV[1]))
	{
		delete	pFont;
	
		printf("Unable to load Font %s\n", _szArgV[1]);

		return	1;
	}

	if (false == pFont->save(_szArgV[2], _szArgV[3]))
	{
		delete	pFont;
	
		printf("Unable to export files %s %s\n", _szArgV[2], _szArgV[3]);

		return	1;
	}

	delete	pFont;

	return	0;
}

void usage()
{
	printf("FontConvert Font.png Out.bin Out.xml\n");
	
	exit(1);
}
