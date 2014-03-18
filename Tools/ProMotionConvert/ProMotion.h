// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <stdint.h>
#include <vector>

struct Frame
{
	int			iDelay;
	uint8_t*	pPalette;
	uint8_t*	pPixels;
};

class ProMotion
{
	public:
		// Constructor
		ProMotion();

		// Destructor
		~ProMotion();

		// Load sprite file
		bool load(const std::string& _strFilename);

		// Save sprite file
		bool save(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

	protected:
		// Number of frames
		int					m_iFrames;

		// Width and height of the sprite
		int					m_iWidth;
		int					m_iHeight;
		
		// Transparent index
		int					m_iTransparentIndex;

		// Vector storage for the frames
		std::vector<Frame>	m_vecFrames;

		// Write PNG
		bool writePNG(const std::string& _strPNGFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

		// Write frame
		void writeFrame(int _iIndex, uint32_t* _pBuffer, int _iStride);
};
