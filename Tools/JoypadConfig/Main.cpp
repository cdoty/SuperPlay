// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <windows.h>
//#include <vld.h>

#include "Config.h"
#include "Log.h"

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _iCmdShow)
{
	ConfigPtr	pConfig	= Config::create();

	// Initialize editor
	if (nullptr == pConfig)
	{
		Log::instance()->logError("Unable to initialize editor interfaces.");

		return	1;
	}

	pConfig->show();

	return	0;
}
