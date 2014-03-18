// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

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

		// Create sprite system
		static ShadowOAM* create();

		// Initialize
		virtual bool initialize();

		// Close
		virtual void close();

		// Render
		virtual void render(int _iLayer);

		// Set sort order
		virtual void setSortOrder(int _iIndex, int _iSortOrder);

		// Set active
		virtual void setActive(int _iIndex, bool _bActive);

		// Clear Objs
		virtual void clearObjs();
		 
		// Get available Obj
		virtual int getAvailableObj();

		// Obj sort
		static int objSort(const void* _pObj1, const void* _pObj2);

	private:
		// Re-sort?
		bool	m_bReSort;

		// Sorted object list

		// Obj array
		tinystl::vector<Obj*>	m_vecSortedObjs;
};

ENDNAMESPACE

