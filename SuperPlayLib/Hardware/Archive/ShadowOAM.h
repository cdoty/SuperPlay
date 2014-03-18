// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#ifdef _DEBUG
#pragma comment(lib, "Expansion_d.lib")
#else
#pragma comment(lib, "Expansion.lib")
#endif

#include "Hardware.h"
#include "Macros.h"
#include "OAM.h"

NAMESPACE(SPlay)

class ShadowOAM : public OAM
{
	typedef	OAM	super;

	public:
		// Constructor
		ShadowOAM();

		// Destructor
		virtual ~ShadowOAM();

		// Create the Shadow OAM
		static ShadowOAM* create();

		// Initialize
		virtual bool initialize();

		// Close
		virtual void close();

		// Render
		virtual void render(int _iLayer);

		// Clear Objs
		virtual void clearObjs();
		 		
		// Get available object
		virtual int getAvailableObject();

	private:
		struct ShadowObj
		{
			// Obj index
			int			iIndex;

			// Used
			bool		bUsed;

			// Link
			ShadowObj*	pNext;

			ShadowObj()	:
				bUsed(false),
				pNext(NULL)
			{
			}
		};

		// Shadow obj array
		ShadowObj*	m_pShadowObjs;

};

ENDNAMESPACE
