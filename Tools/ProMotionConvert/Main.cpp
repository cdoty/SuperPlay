#include <windows.h>
#include <stdio.h>

#include "ProMotion.h"

void Usage();

int main(int _iArgC, char* _szArgV[])
{
	ProMotion	*pProMotion	= NULL;
	
	// Ensure there are three command line parameters plus the .exe filename
	if (_iArgC < 4)
	{
		Usage();
	}
	
	// Create Pro Motion file interface
	pProMotion	= new ProMotion();
	
	// Load the Pro Motion sprite file
	pProMotion->load(_szArgV[1]);
	
	// Save the Pro Motion sprite file
	pProMotion->save(_szArgV[2], _szArgV[3]);
	
	delete	pProMotion;
		
	pProMotion	= NULL;
	
	return	0;
}

void Usage()
{
	printf("PromotionConvert Sprite.spr Out.png Out.xml\n");
	
	exit(1);
}
