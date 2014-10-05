// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <stdio.h>
#include <string.h>

#include "GameDefines.h"
#include "FPS.h"
#include "Hardware.h"

using namespace	SPlay;

FPS::FPS()	:
	m_iCurrentTick(0),
	m_fTickSum(0.0f)
{
	for (int iLoop = 0; iLoop < msc_iMaxSamples; ++iLoop)
	{
		m_tickList[iLoop]	= 0.0f;
	}
}

FPS::~FPS()
{
}

void FPS::update(float _fElapsedTime)
{
	m_fTickSum	-= m_tickList[m_iCurrentTick];

	m_fTickSum	+= _fElapsedTime;

	m_tickList[m_iCurrentTick]	= _fElapsedTime;

	m_iCurrentTick++;

	if (m_iCurrentTick >= msc_iMaxSamples)
	{
		m_iCurrentTick	= 0;
	}

	char	szText[16];

	sprintf(szText, "%6.2f", (float)gsc_iFrameRate * gsc_fFramePeriod / (m_fTickSum / (float)msc_iMaxSamples));

	// Get text layer
	Text*	pText	= Hardware::getText();
	
	// Draw text string to the Text Layer.
	pText->drawText((gsc_iScreenWidth / 8) - 6, (gsc_iScreenHeight / 8) - 1, szText);
}
