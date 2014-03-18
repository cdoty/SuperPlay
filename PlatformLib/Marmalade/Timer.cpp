// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <s3eTimer.h>

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
	m_iTicksPerSecond	= s3eTimerGetUST();

	return	true;
}

void Timer::close()
{
}

void Timer::start()
{
	m_iCurrentTicks	= s3eTimerGetUST();
}

int Timer::getElapsed()
{
	uint64_t	iCurrent	= s3eTimerGetUST();

	int	iCurrentTime;
	
	if (iCurrent >= m_iCurrentTicks)
	{
		iCurrentTime	= static_cast<int>(iCurrent - m_iCurrentTicks);
	}
	
	else
	{
		iCurrentTime	= static_cast<int>(m_iCurrentTicks - iCurrent);
	}
	
	m_iCurrentTicks	= iCurrent;

	return	iCurrentTime;
}

float Timer::getElapsedFloat()
{
	uint64_t	iCurrent	= s3eTimerGetUST();

	double	fCurrentTime;
	
	if (iCurrent >= m_iCurrentTicks)
	{
		fCurrentTime	= static_cast<double>(iCurrent - m_iCurrentTicks) / 1000.0f;
	}
	
	else
	{
		fCurrentTime	= static_cast<double>(m_iCurrentTicks - iCurrent) / 1000.0f;
	}
	
	m_iCurrentTicks	= iCurrent;

	return	static_cast<float>(fCurrentTime);
}

ENDNAMESPACE
