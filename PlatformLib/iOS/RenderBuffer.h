// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <OpenGLES/ES1/gl.h>

#include "Macros.h"

NAMESPACE(SPlay)

class RenderBuffer
{
	public:
		// Constructor
		RenderBuffer();

		// Destructor
		~RenderBuffer();

		// Initialize
		bool initialize();

		// Close
		void close();

		// Bind framebuffer
		void bindFrameBuffer();

		// Bind renderbuffer
		void bindRenderBuffer();

		// Get framebuffer
		GLuint getFrameBuffer() {return m_uFrameBuffer;}

		// Get renderbuffer
		GLuint getRenderBuffer() {return m_uRenderBuffer;}

	private:
		// Frame buffer
		GLuint	m_uFrameBuffer;

		// Render buffer
		GLuint	m_uRenderBuffer;
};

ENDNAMESPACE
