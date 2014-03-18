// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include "HardwareDefines.h"
#include "Macros.h"

NAMESPACE(SPlay)

class ISpriteBatch;

class Obj
{
	public:
		// Constructor
		Obj();

		// Destructor
		~Obj();

		// Create
		static Obj* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Render
		void render(ISpriteBatch* _pSpriteBatch, int _iTexture, int _iLayer, float _fZ);

		// Clear
		void clear();

		// Set position
		void setPosition(float _fX, float _fY) {m_fX = _fX; m_fY = _fY;}

		// Set tile number
		void setTileNumber(int _iTileNumber);

		// Set sprite size
		void setObjSize(ObjSize _eObjSize);

		// Get active
		bool getActive() const {return m_bActive;}

		// Set active
		void setActive(bool _bActive) {m_bActive = _bActive;}

		// Set BG
		void setBG(int _iLayer) {m_iLayer = _iLayer;}

		// Get flip
		Flip getFlip() const {return m_eFlip;}

		// Set flip
		void setFlip(Flip _eFlip);

		// Get sort order
		int getSortOrder() const {return m_iSortOrder;}

		// Set sort order
		void setSortOrder(int _iSortOrder) {m_iSortOrder = _iSortOrder;}

		// Get used
		bool getUsed() const {return m_bUsed;}

		// Set used
		void setUsed(bool _bUsed) {m_bUsed = _bUsed;}

	private:
		// Position
		float	m_fX;
		float	m_fY;

		// Sort order
		int		m_iSortOrder;

		// Tile number
		int		m_iTileNumber;

		// Sprite size
		ObjSize	m_eObjSize;

		// Layer
		int		m_iLayer;

		// Sprite flip
		Flip	m_eFlip;

		// Texture UVs
		float	m_fU1;
		float	m_fV1;
		float	m_fU2;
		float	m_fV2;

		// Active?
		bool	m_bActive;

		// Used
		bool	m_bUsed;

		// Update UVs
		void updateUVs();

		// Get width
		float getWidth();

		// Get height
		float getHeight();
};

ENDNAMESPACE
