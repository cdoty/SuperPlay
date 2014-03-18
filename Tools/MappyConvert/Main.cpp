// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <math.h>
#include <stdio.h>

#include "File.h"
#include "Functions.h"
#include "HardwareDefines.h"
#include "Log.h"
#include "MappyMap.h"
#include "File.h"
#include "LodePNG/LodePNG.h"

void usage();
bool convertTiles(const char* _szFilename, int& _iTextureWidth, int& _iTextureHeight);
bool writeMapInfo(const char* _szFilename, const std::string& _strTileName, const std::string& _strMapName, int _iTextureWidth, 
	int _iTextureHeight);

bool convertMap(const char* _szFilename);
bool writeBufferToFile(const std::string& _strFilename, const uint8_t* _pBuffer, int _iLength);

int main(int _iArgC, char* _szArgV[])
{
	int iTextureWidth	= 0;
	int iTextureHeight	= 0;
	
	// Ensure there are four command line parameters plus the .exe filename
	if (_iArgC != 5)
	{
		usage();
	}

	// Load the map
	if (-1 == MapLoad(_szArgV[1]))
	{
		printf("Unable to load map %s.\n", _szArgV[1]);

		return	1;
	}
	
	// Convert tiles
	if (false == convertTiles(_szArgV[2], iTextureWidth, iTextureHeight))
	{
		printf("Unable to convert tiles.\n");

		return	1;
	}	
	
	// Convert map
	if (false == convertMap(_szArgV[3]))
	{
		printf("Unable to convert map.\n");

		return	1;
	}

	// Write map info
	if (false == writeMapInfo(_szArgV[4], _szArgV[2], _szArgV[3], iTextureWidth, iTextureHeight))
	{
		printf("Unable to write map info file.\n");

		return	1;
	}

	// Free the memory used by the map
	MapFreeMem();
	
	return	0;
}

void usage()
{
	printf("MappyConvert TileMap.fmp Out.png Out.map Out.xml\n");
	
	exit(1);
}

// Converts tiles, assumes tiles are 8 bit.
bool convertTiles(const char* _szFilename, int& _iTextureWidth, int& _iTextureHeight)
{
	// Find the output width
	_iTextureWidth	= mapblockwidth;
	
	if ((_iTextureWidth % mapblockwidth) != 0)
	{
		Log::instance()->logError("Block width needs be a multiple of 16\n");
		
		return	false;
	}
	
	// Find the output height
	_iTextureHeight	= mapblockheight * mapnumblockgfx;
	
	if ((_iTextureHeight % mapblockheight) != 0)
	{
		Log::instance()->logError("Block height needs be a multiple of 16\n");
		
		return	false;
	}
	
	// Find the number of blocks wide and high the texture is
	int	iBlocksWide	= _iTextureWidth / mapblockwidth;
	int	iBlocksHigh	= _iTextureHeight / mapblockheight;
	
	// Set up a pointer to the start of the BLKSTR buffer
	BLKSTR*	pBlock	= reinterpret_cast<BLKSTR*>(mapblockstrpt);
		
	// Allocate and clear memory for the tiles and the tile palette index
	uint32_t*	pTileBuffer	= new uint32_t[_iTextureWidth * _iTextureHeight];
	
	memset(pTileBuffer, 0, _iTextureWidth * _iTextureHeight * 4);
	
	int	iBlockX	= 0;
	int	iBlockY	= 0;
	
	// Convert the graphics
	for (int iLoop = 1; iLoop < mapnumblockgfx; iLoop++)
	{
		uint32_t*	pBuffer	= (uint32_t*)(mapblockgfxpt + iLoop * mapblockwidth * mapblockheight * 4);
		uint32_t*	pTile	= &pTileBuffer[iBlockY * _iTextureWidth * mapblockheight + iBlockX * mapblockwidth];
				
		// Convert the pixels
		for (int iYLoop = 0; iYLoop < mapblockheight; iYLoop++)
		{
			for (int iXLoop = 0; iXLoop < mapblockwidth; iXLoop++)
			{
				// Save the pixel
				*pTile	= *pBuffer;
				
				pBuffer++;
				pTile++;
			}
			
			pTile	+= _iTextureWidth - mapblockwidth;
		}

		iBlockX++;
		
		if (iBlockX >= iBlocksWide)
		{
			iBlockX	= 0;
			iBlockY++;	
		}
	}

	if (false == File::createDirectory(Functions::getDirectoryFromPath(_szFilename)))
	{
		return	false;
	}

	if (LodePNG_encode32_file(_szFilename, (uint8_t*)pTileBuffer, _iTextureWidth, _iTextureHeight) != 0)
	{
		return	false;
	}
	
	return	true;
}

bool writeMapInfo(const char* _szFilename, const std::string& _strTileName, const std::string& _strMapName, int _iTextureWidth, 
	int _iTextureHeight)
{
	std::string	strTextureName;
	
	strTextureName	= Functions::getFilenameFromPath(_strTileName);
	strTextureName	+= ".png";
	
	std::string	strMapName;

	strMapName	= Functions::getFullFilenameFromPath(_strMapName);

	// Find the number of blocks wide and high the texture is
	int	iBlocksWide	= _iTextureWidth / mapblockwidth;
	int	iBlocksHigh	= _iTextureHeight / mapblockheight;

	if (false == File::createDirectory(Functions::getDirectoryFromPath(_szFilename)))
	{
		return	false;
	}

	File*	pFile	= new File();

	if (false == pFile->create(_szFilename))
	{
		return	false;
	}
	
	if (false == pFile->writeString("<MapInfo>\n"))
	{
		return	false;
	}
	
	char	szString[FILENAME_MAX];
	
	sprintf(szString, "\t<ImageName>%s</ImageName>\n", strTextureName.c_str());

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
	
	sprintf(szString, "\t<MapName>%s</MapName>\n", strMapName.c_str());

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
	
	sprintf(szString, "\t<TileWidth>%d</TileWidth>\n", mapblockwidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
	
	sprintf(szString, "\t<TileHeight>%d</TileHeight>\n", mapblockheight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
	
	sprintf(szString, "\t<MapWidth>%d</MapWidth>\n", mapwidth);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
	
	sprintf(szString, "\t<MapHeight>%d</MapHeight>\n", mapheight);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
	
	sprintf(szString, "\t<TileCount>%d</TileCount>\n", mapnumblockgfx);

	if (false == pFile->writeString(szString))
	{
		return	false;
	}
		
	if (false == pFile->writeString("</MapInfo>\n"))
	{
		return	false;
	}
	
	pFile->close();
	
	delete	pFile;
	
	return	true;
}

// Converts the map
bool convertMap(const char* _szFilename)
{
	uint16_t*	pMapPtr	= (uint16_t*)mapmappt[0];
	
	SPlay::TileInfo*	pMapBuffer	= new SPlay::TileInfo[mapwidth * mapheight];
	
	BLKSTR	*pBlock	= (BLKSTR*)mapblockstrpt;

	for (int iLoop = 0; iLoop < mapwidth * mapheight; iLoop++)
	{
		int	iTileNumber;

		// Handle blank tiles. These are usually created when the map is resized.
		if (0 == pMapPtr[iLoop])
		{
			iTileNumber	= 0;
		}
		
		else
		{
			// Tile 0 is not exported.
			iTileNumber	= pMapPtr[iLoop];
		}
		
		pMapBuffer[iLoop].iTileIndex	= pBlock[iTileNumber].bgoff - 1;
		pMapBuffer[iLoop].eFlip			= SPlay::NoFlip;

		if (pBlock[iTileNumber].unused2 != 0)
		{
			if (pBlock[iTileNumber].unused3 != 0)
			{
				pMapBuffer[iLoop].eFlip	= SPlay::HVFlip;
			}

			else
			{
				pMapBuffer[iLoop].eFlip	= SPlay::HFlip;
			}
		}

		else if (pBlock[iTileNumber].unused3 != 0)
		{
			pMapBuffer[iLoop].eFlip	= SPlay::VFlip;
		}
	}

	if (false == writeBufferToFile(_szFilename, (uint8_t*)pMapBuffer, mapwidth * mapheight * sizeof(SPlay::TileInfo)))
	{
		return	false;
	}
	  
	// Free memory used to tilemaps.
	delete [] pMapBuffer;
		
	pMapBuffer	= NULL;

	return	true;
}

bool writeBufferToFile(const std::string& _strFilename, const uint8_t* _pBuffer, int _iLength)
{
	if (false == File::createDirectory(Functions::getDirectoryFromPath(_strFilename)))
	{
		return	false;
	}

	File*	pFile	= new File();

	if (false == pFile->create(_strFilename, true))
	{
		Log::instance()->logError("Unable to create file %s.\n", _strFilename.c_str()); 

		return	false;
	}
	
	if (false == pFile->writeBuffer(_pBuffer, _iLength))
	{
		Log::instance()->logError("Unable to write to file %s.\n", _strFilename.c_str()); 

		return	false;
	}
	
	pFile->close();
	
	delete	pFile;

	return	true;
}
