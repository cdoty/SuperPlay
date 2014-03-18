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
#include "RenderBuffer.h"

// Initialize
bool initialize(int _iWindowWidth, int _iWindowHeight);

NAMESPACE(SPlay)

class Platform
{
	public:
		// Initialize
		static bool initialize();
		
		// Close
		static void close();
		
		// Update
		static bool update(float _fElapsed);

		// Stop
		static void stop();

		// Redraw
		static void redraw();

    	// Set window size
    	static void setWindowSize(int _iWindowWidth, int _iWindowHeight)  {ms_iWindowWidth = _iWindowWidth; ms_iWindowHeight = _iWindowHeight;}

        // Get storage path
        static const tinystl::string& getStoragePath() {return ms_strStoragePath;}
    
        // Get resource path
        static const tinystl::string& getResourcePath() {return ms_strResourcePath;}

        // Set resource path
        static const void setResourcePath(const char* _szResourcePath) {ms_strResourcePath = _szResourcePath;}

		// Create render buffer
		static bool createRenderBuffer();

		// Setup render buffer
		static bool setupRenderBuffer();

	private:
		// Render buffer
		static RenderBuffer*	ms_pRenderBuffer;

		// Window size
		static int 		ms_iWindowWidth;
		static int 		ms_iWindowHeight;

        // Storage path
        static tinystl::string ms_strStoragePath;
    
		// Resource path
		static tinystl::string ms_strResourcePath;
    
        // Set storage path
        static void setStoragePath();
};

ENDNAMESPACE
