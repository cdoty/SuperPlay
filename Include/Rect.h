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
#include "Point.h"

NAMESPACE(SPlay)

class Rect
{
	public:
		// Rect position
		int	iLeft;
		int	iTop;

		// Rect size
		int	iWidth;
		int	iHeight;

		Rect()	:
			iLeft(0),
			iTop(0),
			iWidth(0),
			iHeight(0)
		{
		}

		Rect(int _iLeft, int _iTop, int _iWidth, int _iHeight)	:
			iLeft(_iLeft),
			iTop(_iTop),
			iWidth(_iWidth),
			iHeight(_iHeight)
		{
		}
		
		// Operator+ overload
		Rect(const Rect& _rctRect)	:
			iLeft(_rctRect.iLeft),
			iTop(_rctRect.iTop),
			iWidth(_rctRect.iWidth),
			iHeight(_rctRect.iHeight)
		{
		}

		// Operator= overload
		Rect& operator= (Rect& _rctRect)
		{
	  		iLeft	= _rctRect.iLeft;
	  		iWidth	= _rctRect.iWidth;
	  		iTop	= _rctRect.iTop;
	  		iHeight	= _rctRect.iHeight;

			return	*this;
		}

		// Bottom position
		int bottom() const {return iTop + iHeight;}

		// Left position
		int right() const {return iLeft + iWidth;}

		// Set
		void set(const Rect& _rctRect)
		{
			iLeft	= _rctRect.iLeft;
			iTop	= _rctRect.iTop;
			iWidth	= _rctRect.iWidth;
			iHeight	= _rctRect.iHeight;
		}
		
		// Reset 
		void reset()
		{
			iLeft	= 0;
			iTop	= 0;
			iWidth	= 0;
			iHeight	= 0;
		}

		// Point in rect?
		bool pointInRect(const Point& _ptPoint) const
		{
			if (_ptPoint.iX >= iLeft && _ptPoint.iX < right() && _ptPoint.iY >= iTop && _ptPoint.iY < bottom())
			{
				return	true;
			}
			
			return	false;
		}


		// Intersects rect? Does not detect a rect inside another rect, only if an edge intersect the rect.
		// Check the smaller rect against the bigger rect to avoid the inside rect issue.
		bool intersectsRect(const Rect& _rctRect) const
		{
			if (((_rctRect.iLeft >= iLeft && _rctRect.iLeft < right()) || (_rctRect.right() >= iLeft && _rctRect.right() < right())) &&
				((_rctRect.iTop >= iTop && _rctRect.iTop < bottom()) || (_rctRect.bottom() >= iTop && _rctRect.bottom() < bottom())))
			{
				return	true;
			}
			
			return	false;
		}
};

ENDNAMESPACE
