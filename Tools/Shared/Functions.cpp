// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <direct.h>

#include "Functions.h"

std::string Functions::getFilenameFromPath(const std::string& _strPath)
{
	char	szFilename[FILENAME_MAX];
	char	szExtension[FILENAME_MAX];

	_splitpath(_strPath.c_str(), NULL, NULL, szFilename, szExtension);

	return	szFilename;
}

std::string Functions::getExtensionFromPath(const std::string& _strPath)
{
	char	szExtension[FILENAME_MAX];

	_splitpath(_strPath.c_str(), NULL, NULL, NULL, szExtension);

	return	szExtension;
}

std::string Functions::getFullFilenameFromPath(const std::string& _strPath)
{
	char	szFilename[FILENAME_MAX];
	char	szExtension[FILENAME_MAX];

	_splitpath(_strPath.c_str(), NULL, NULL, szFilename, szExtension);

	std::string	strFilename;

	strFilename	= szFilename;
	strFilename	+= szExtension;
	
	return	strFilename;
}

std::string Functions::getDirectoryFromPath(const std::string& _strPath)
{
	char	szDrive[FILENAME_MAX];
	char	szDir[FILENAME_MAX];

	_splitpath(_strPath.c_str(), szDrive, szDir, NULL, NULL);

	std::string	strDirectory;

	strDirectory	= szDrive;
	strDirectory	+= szDir;
	
	return	strDirectory;
}

int Functions::convertStringToInt(const std::string& _strString)
{
	return	strtol(_strString.c_str(), NULL, 0);
}
