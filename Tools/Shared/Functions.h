// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <string>

class Functions
{
	public:
		// Get filename from path
		static std::string getFilenameFromPath(const std::string& _strPath);

		// Get xtension from path
		static std::string getExtensionFromPath(const std::string& _strPath);

		// Get filename + extension from path
		static std::string getFullFilenameFromPath(const std::string& _strPath);

		// Get directory from path
		static std::string getDirectoryFromPath(const std::string& _strPath);

		// Create path, ensuring each directory exists along the way
		static bool createPath(const std::string& _strDirectory);

		// Convert int string to int
		static int convertStringToInt(const std::string& _strString);

		// Log2
		static double log2(double _fNumber)
		{  
			return	log(_fNumber) / log(2.0f);  
		}
};
