// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <TinySTL/stdint.h>
#include <math.h>
#include <stdlib.h>

#include "Utilities.h"

NAMESPACE(SPlay)

double Utilities::log2(double _fValue)
{  
	return	log(_fValue) / log(2.0f);  
}

int Utilities::getHash(const tinystl::string& _strString)
{
    uint32_t	iHash	= 5381;
    
    int	t_c	= static_cast<int>(_strString.size());

    for (int iLoop = 0; iLoop < t_c; ++iLoop)
    {
		iHash	= ((iHash << 5) + iHash) + _strString[iLoop];
    }

    return	iHash;
}

int Utilities::convertStringToInt(const tinystl::string& _strString)
{
	return	static_cast<int>(strtol(_strString.c_str(), NULL, 0));
}

ENDNAMESPACE
