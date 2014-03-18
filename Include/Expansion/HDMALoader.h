// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/string.h>

#include "Macros.h"

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "Expansion_d.lib")
#else
#pragma comment(lib, "Expansion.lib")
#endif
#endif

NAMESPACE(SPlay)

class HDMALoader
{
	public:
		// Constructor
		HDMALoader();

		// Destructor
		virtual ~HDMALoader();

		// Create the HDMA loader
		static HDMALoader* create(const tinystl::string& _strFilename, const tinystl::string& _strSubDirectory = "");

		// Initialize
		bool initialize(const tinystl::string& _strFilename, const tinystl::string& _strSubDirectory);

		// Close
		void close();

	private:
		// Sub directory
		tinystl::string	m_strSubDirectory;

		// HDMA table
		uint32_t*	m_pHDMATable;

		// Table height
		int			m_iHeight;

		// Load image
		bool loadImage(const tinystl::string& _strFilename);

		// Transfer HDMA
		bool transferHDMA();
};

ENDNAMESPACE
