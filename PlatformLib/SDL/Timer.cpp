// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <SDL.h>

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
	m_iTicksPerSecond	= SDL_GetPerformanceFrequency();

	return	true;
}

void Timer::close()
{
}

void Timer::start()
{
	m_iCurrentTicks	= SDL_GetPerformanceCounter();
}

int Timer::getElapsed()
{
	Uint64	iCurrent	= SDL_GetPerformanceCounter();

	int	iCurrentTime;
	
	if (iCurrent >= m_iCurrentTicks)
	{
		iCurrentTime	= static_cast<int>(static_cast<double>(iCurrent - m_iCurrentTicks) / 
			static_cast<double>(m_iTicksPerSecond) * 1000.0f);
	}
	
	else
	{
		iCurrentTime	= static_cast<int>(static_cast<double>(m_iCurrentTicks - iCurrent) / 
			static_cast<double>(m_iTicksPerSecond) * 1000.0f);
	}
	
	m_iCurrentTicks	= iCurrent;

	return	iCurrentTime;
}

float Timer::getElapsedFloat()
{
	Uint64	iCurrent	= SDL_GetPerformanceCounter();

	double	fCurrentTime;
	
	if (iCurrent >= m_iCurrentTicks)
	{
		fCurrentTime	= static_cast<double>(iCurrent - m_iCurrentTicks) / static_cast<double>(m_iTicksPerSecond);
	}
	
	else
	{
		fCurrentTime	= static_cast<double>(m_iCurrentTicks - iCurrent) / static_cast<double>(m_iTicksPerSecond);
	}
	
	m_iCurrentTicks	= iCurrent;

	return	static_cast<float>(fCurrentTime);
}

ENDNAMESPACE
