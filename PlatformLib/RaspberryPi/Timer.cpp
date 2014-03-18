// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <time.h>

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
	timespec	timeSpec;
	
	clock_gettime(CLOCK_MONOTONIC, &timeSpec);
	
	m_iCurrentTime	= timeSpec.tv_sec * 1000000 + (timeSpec.tv_nsec / 1000);
}

int Timer::getElapsed()
{
	timespec	timeSpec;
	
	clock_gettime(CLOCK_MONOTONIC, &timeSpec);
	
	int64_t	iLastTime	= m_iCurrentTime;
	
	m_iCurrentTime	= timeSpec.tv_sec * 1000000 + (timeSpec.tv_nsec / 1000);

	return	(m_iCurrentTime - iLastTime) / 1000;
}

float Timer::getElapsedFloat()
{
	timespec	timeSpec;
	
	clock_gettime(CLOCK_MONOTONIC, &timeSpec);
	
	int64_t	iLastTime	= m_iCurrentTime;
	
	m_iCurrentTime	= timeSpec.tv_sec * 1000000 + (timeSpec.tv_nsec / 1000);

	return	static_cast<float>(m_iCurrentTime - iLastTime) / 1000000.0f;
}

ENDNAMESPACE
