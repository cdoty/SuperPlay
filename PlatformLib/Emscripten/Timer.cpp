// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <emscripten.h>

#include "Log.h"
#include "Timer.h"

NAMESPACE(SPlay)

Timer::Timer()
{
}

Timer::~Timer()
{
	close();
}

Timer* Timer::create()
{
	Timer*	pTimer	= new Timer();
	
	if (false == pTimer->initialize())
	{
		delete	pTimer;
		
		pTimer	= NULL;
	}
	
	return	pTimer;
}

bool Timer::initialize()
{
	return	true;
}

void Timer::close()
{
}

void Timer::start()
{
	// Get current time, in milliseconds
	m_fCurrentTime	= emscripten_get_now() / 1000.0f;
}

float Timer::getElapsedFloat()
{
	float	fCurrent	= emscripten_get_now() / 1000.0f;

	float	fTime	= fCurrent - m_fCurrentTime;
	
	m_fCurrentTime	= fCurrent;

	return	fTime;
}

ENDNAMESPACE
