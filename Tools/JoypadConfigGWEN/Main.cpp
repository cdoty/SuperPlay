// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "Config.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/ListBox.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"

#ifdef _DEBUG
#pragma comment (lib, "gwen_staticd.lib")
#else
#pragma comment (lib, "gwen_static.lib")
#endif

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _iCmdShow)
{
	Config*	pConfig	= Config::create();

	if (NULL == pConfig)
	{
		return	1;
	}

	pConfig->run();

	delete	pConfig;

	return	0;
}