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

#include "NAnim.h"

void usage();

int main(int _iArgC, char* _szArgV[])
{
  	// Ensure there are three command line parameters plus the .exe filename
	if (_iArgC != 4)
	{
		usage();
	}

	NAnim*	pNAnim	= NAnim::create();

	if (NULL == pNAnim)
	{
		printf("Unable to create NAnim interface\n");

		return	1;
	}

	if (false == pNAnim->load(_szArgV[1]))
	{
		delete	pNAnim;
	
		printf("Unable to load NAnim file %s\n", _szArgV[1]);

		return	1;
	}

	if (false == pNAnim->save(_szArgV[2], _szArgV[3]))
	{
		delete	pNAnim;
	
		printf("Unable to export files %s %s\n", _szArgV[2], _szArgV[3]);

		return	1;
	}

	delete	pNAnim;

	return	0;
}

void usage()
{
	printf("NAnimConvert Sprite.nanim Out.png Out.xml\n");
	
	exit(1);
}
