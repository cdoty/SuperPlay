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
#include <string>
#include <vector>

#include "File.h"
#include "nanim.pb.h"
#include "NAnimStructs.h"

class NAnim
{
	public:
		// Constructor
		NAnim();

		// Destructor
		~NAnim();

		// Create
		static NAnim* create();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Load
		bool load(const std::string& _strFilename);

		// Save
		bool save(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

	private:
		struct SpriteFrame
		{
			// Size
			int			iWidth;
			int			iHeight;

			// Image
			uint32_t*	pImage;
		};

		// Frames
		std::vector<NAnimFrame>	m_vecFrames;

		// Images
		std::vector<NAnimImage>	m_vecImages;

		// Frame size
		int	m_iFrameWidth;
		int	m_iFrameHeight;

		// Sprite frames
		std::vector<SpriteFrame>	m_vecSpriteFrames;

		// Load animations
		bool loadAnimations(const im::bci::nanim::Nanim& _anim);

		// Load images
		bool loadImages(const im::bci::nanim::Nanim& _anim);

		// Load frame
		bool loadFrame(const im::bci::nanim::Frame& _frame);

		// Load image
		bool loadImage(const im::bci::nanim::Image& _image);

		// Extract frames
		bool extractFrames();

		// Write PNG
		bool writePNG(const std::string& _strFilename);

		// Write XML
		bool writeXML(const std::string& _strPNGFilename, const std::string& _strXMLFilename);

		// Get image size
		bool getImageSize(const std::string& _strImageName, int& _iWidth, int& _iHeight);

		// Get image buffer
		uint32_t* getImageBuffer(const std::string& _strImageName);
};

