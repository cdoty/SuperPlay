// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "BaseSprite.h"

using namespace SPlay;

class BulletSprite : public BaseSprite
{
	typedef	BaseSprite	super;

	public:
		// Constructor
		BulletSprite(int _iTileIndex);

		// Destructor
		virtual ~BulletSprite();

		// Create
		static BulletSprite* create(int _iTileIndex);

		// Initialize
		virtual bool initialize();

		// Close
		virtual void close();
};
