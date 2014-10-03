// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <ppapi_simple/ps_main.h>
#include <sys/mount.h>

#include "Log.h"
#include "Platform.h"
#include "SPlayInstance.h"
#include "System.h"
#include "Timer.h"

void* SPlayCreate(PP_Instance _instance, PSMainFunc_t _function)
{
	SPlay::SPlayInstance*	pInstance	= new SPlay::SPlayInstance(_instance);
	
	pInstance->SetMain(_function);
	
	SPlay::Platform::setInstance(pInstance);

	return	pInstance;
}

int splay_main(int argc, char *argv[])
{
	PSEventSetFilter(PSE_ALL);

	mount("NaCl", "/", "httpfs", 0, "");

	SPlay::Platform::runLoop();

	SPlay::System::close();
	
	return	0;
}

PPAPI_SIMPLE_USE_MAIN(SPlayCreate, splay_main);

