// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "Macros.h"
#include "Rect.h"
#include "RenderParams.h"

NAMESPACE(SPlay)

class ISpriteBatch
{
	public:
		// Destructor
		virtual ~ISpriteBatch() {}

		// Start batch
		virtual void startBatch(const Rect& _rctClip) = 0;
		virtual void startBatch() = 0;

		// Add sprite
		virtual void addSprite(const RenderParams& _renderParams) = 0;

		// End batch
		virtual void endBatch() = 0;
};

// Create sprite batch
extern ISpriteBatch* createSpriteBatch(int _iSprites = 64);

ENDNAMESPACE
