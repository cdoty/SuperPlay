// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
	LARGE_INTEGER	iTicksPerSec;

    // Get the ticks per second, from the performance counter
	if (false == QueryPerformanceFrequency(&iTicksPerSec))
	{
		Log::instance()->logError("QueryPerformanceFrequency failed.");
		
		return	false;
	}
    
	m_iTicksPerSecond.QuadPart	= iTicksPerSec.QuadPart;

	return	true;
}

void Timer::close()
{
}

void Timer::start()
{
	LARGE_INTEGER	iCurrent;

	QueryPerformanceCounter(&iCurrent);
	
	m_iCurrentTicks.QuadPart	= iCurrent.QuadPart;
}

int Timer::getElapsed()
{
	LARGE_INTEGER	iCurrent;

	QueryPerformanceCounter(&iCurrent);

	int	iCurrentTime;
	
	if (iCurrent.QuadPart >= m_iCurrentTicks.QuadPart)
	{
		iCurrentTime	= static_cast<int>(static_cast<double>(iCurrent.QuadPart - m_iCurrentTicks.QuadPart) / 
			static_cast<double>(m_iTicksPerSecond.QuadPart) * 1000.0f);
	}
	
	else
	{
		iCurrentTime	= static_cast<int>(static_cast<double>(m_iCurrentTicks.QuadPart - iCurrent.QuadPart) / 
			static_cast<double>(m_iTicksPerSecond.QuadPart) * 1000.0f);
	}
	
	m_iCurrentTicks.QuadPart	= iCurrent.QuadPart;

	return	iCurrentTime;
}

float Timer::getElapsedFloat()
{
	LARGE_INTEGER	iCurrent;

	QueryPerformanceCounter(&iCurrent);

	double	fCurrentTime;
	
	if (iCurrent.QuadPart >= m_iCurrentTicks.QuadPart)
	{
		fCurrentTime	= static_cast<double>(iCurrent.QuadPart - m_iCurrentTicks.QuadPart) / static_cast<double>(m_iTicksPerSecond.QuadPart);
	}
	
	else
	{
		fCurrentTime	= static_cast<double>(m_iCurrentTicks.QuadPart - iCurrent.QuadPart) / static_cast<double>(m_iTicksPerSecond.QuadPart);
	}
	
	m_iCurrentTicks.QuadPart	= iCurrent.QuadPart;

	return	static_cast<float>(fCurrentTime);
}

ENDNAMESPACE
