// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/vector.h>

#include "Macros.h"
#include "Obj.h"

NAMESPACE(SPlay)

struct	RenderParams;
class	ISpriteBatch;
class	ShadowOAM;

class OAM
{
	public:
		// Constructor
		OAM();

		// Destructor
		virtual ~OAM();

		// Create sprite system
		static OAM* create();

		// Initialize
		virtual bool initialize();

		// Close
		virtual void close();

		// Render
		virtual void render(int _iLayer);

		// Set position
		void setPosition(int _iIndex, float _fX, float _fY);
		
		// Set tile number
		void setTileNumber(int _iIndex, int _iTileNumber);

		// Set size
		void setObjSize(int _iIndex, ObjSize _eObjSize);

		// Get active
		bool getActive(int _iIndex);

		// Set active
		virtual void setActive(int _iIndex, bool _bActive);

		// Set BG
		void setBG(int _iIndex, int _iLayer);

		// Get flip
		Flip getFlip(int _iIndex);

		// Set flip
		void setFlip(int _iIndex, Flip _eFlip);

		// Set sort order
		virtual void setSortOrder(int _iIndex, int _iSortOrder);

		// Set used
		void setUsed(int _iIndex, bool _bUsed);

		// Clear Objs
		virtual void clearObjs();
		 
		// Get available Obj
		virtual int getAvailableObj();

	protected:
		// Sprite batch
		ISpriteBatch*		m_pSpriteBatch;

		// Obj array
		Obj*				m_pObjs[gsc_iMaxObjs];
};

ENDNAMESPACE
