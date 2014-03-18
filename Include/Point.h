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

class Point
{
	public:
		int	iX;
		int	iY;
		
		Point()	:
			iX(0),
			iY(0)
		{
		}		

		Point(int _iX, int _iY)	:
			iX(_iX),
			iY(_iY)
		{
		}		

		Point(const Point& _ptPoint)	:
			iX(_ptPoint.iX),
			iY(_ptPoint.iY)
		{
		}

		// Set
		void set(const Point& _ptPoint)
		{
			iX	= _ptPoint.iX;
			iY	= _ptPoint.iY;
		}

		// Reset 
		void reset()
		{
			iX	= 0;
			iY	= 0;
		}

		// Operator= overload
		Point& operator= (const Point& _ptPoint)
		{
			iX	= _ptPoint.iX;
			iY	= _ptPoint.iY;

			return	*this;
		}

		// Operator+ overload
		Point operator+ (const Point& _ptPoint)
		{
			Point	ptTemp;

			ptTemp.iX	= iX + _ptPoint.iX;
			ptTemp.iY	= iY + _ptPoint.iY;

			return	ptTemp;
		}

		// Operator+= overload
		Point operator+= (const Point& _ptPoint)
		{
			Point	ptTemp;

			iX += _ptPoint.iX;
			iY += _ptPoint.iY;

			return	*this;
		}

		// Operator+ overload
		Point operator- (const Point& _ptPoint)
		{
			Point	ptTemp;

			ptTemp.iX	= iX - _ptPoint.iX;
			ptTemp.iY	= iY - _ptPoint.iY;

			return	ptTemp;
		}

		// Operator+= overload
		Point operator-= (const Point& _ptPoint)
		{
			Point	ptTemp;

			iX -= _ptPoint.iX;
			iY -= _ptPoint.iY;

			return	*this;
		}

		// Operator/ overload
		Point operator/ (int _iDivisor)
		{
			Point	ptTemp;

			ptTemp.iX	= iX / _iDivisor;
			ptTemp.iY	= iY / _iDivisor;

			return	ptTemp;
		}

		// Operator+= overload
		Point operator/= (int _iDivisor)
		{
			Point	ptTemp;

			iX /= _iDivisor;
			iY /= _iDivisor;

			return	*this;
		}
};

ENDNAMESPACE
