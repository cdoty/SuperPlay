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

#include "ASE.h"

void usage();

int main(int _iArgC, char* _szArgV[])
{
	// Ensure there are three command line parameters plus the .exe filename
	if (_iArgC != 4)
	{
		usage();
	}

	ASE*	pASE	= ASE::create();

	if (NULL == pASE)
	{
		printf("Unable to create ASE interface\n");

		return	1;
	}

	if (false == pASE->load(_szArgV[1]))
	{
		delete	pASE;
	
		printf("Unable to load ASE %s\n", _szArgV[1]);

		return	1;
	}

	if (false == pASE->save(_szArgV[2], _szArgV[3]))
	{
		delete	pASE;
	
		printf("Unable to export files %s %s\n", _szArgV[2], _szArgV[3]);

		return	1;
	}

	delete	pASE;

	return	0;
}

void usage()
{
	printf("ASEConvert Sprite.ase Out.png Out.xml\n");
	
	exit(1);
}
