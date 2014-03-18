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

NAMESPACE(SPlay)

class IIndexBuffer
{
	public:
		// Destructor
		virtual ~IIndexBuffer() {}

		// Get buffer
		virtual void* getBuffer(int& _iIndices) const = 0;

		// Release buffer
		virtual void releaseBuffer() = 0;

		// Get index count
		virtual int getIndexCount() const = 0;
};

ENDNAMESPACE
