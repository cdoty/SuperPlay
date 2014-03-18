// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <process.h>
#include <stdio.h>

#include "Tiled.h"

void usage();

int main(int _iArgC, char* _szArgV[])
{
	// Ensure there are four command line parameters plus the .exe filename
	if (_iArgC != 5)
	{
		usage();
	}

	Tiled*	pTiled	= Tiled::create();

	if (NULL == pTiled)
	{
		printf("Unable to create Tiled interface\n");

		return	1;
	}

	if (false == pTiled->load(_szArgV[1]))
	{
		printf("Unable to load Tiled file %s\n", _szArgV[1]);

		return	1;
	}

	if (false == pTiled->save(_szArgV[2], _szArgV[3], _szArgV[4]))
	{
		printf("Unable to save map %s %s %s\n", _szArgV[2], _szArgV[3], _szArgV[4]);

		return	1;
	}

	return	0;
}

void usage()
{
	printf("TiledConvert TileMap.tmx Out.png Out.map Out.xml\n");
	
	exit(1);
}
