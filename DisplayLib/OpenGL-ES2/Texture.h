// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <TargetConditionals.h>
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#include <OpenGL/gl.h>
#endif
#elif defined __ANDROID__ || defined EMSCRIPTEN || defined NACL || defined ANGLE
#include <GLES2/gl2.h>
#elif defined MARMALADE
#include <IwGL.h>
#else
#include <GL/gl.h>
#endif

#include <TinySTL/stdint.h>

#include "ITexture.h"
#include "Macros.h"

NAMESPACE(SPlay)

class Texture : public ITexture
{
	public:
		// Constructor
		Texture();

		// Destructor
		~Texture();

		// Create
		bool create(int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic);
		
		// Close
		void close();

		// Get texture width and height
		virtual void getSize(int& _iTextureWidth, int& _iTextureHeight) const;

		// Get image width
		virtual int getImageWidth() const {return m_iImageWidth;}
		
		// Get image height
		virtual int getImageHeight() const {return m_iImageHeight;}
		
		// Get texture width
		virtual int getTextureWidth() const {return m_iTextureWidth;}
		
		// Get texture height
		virtual int getTextureHeight() const {return m_iTextureHeight;}
		
		// Get texture
		GLuint getTexture() const {return m_uTextureID;}

		// Get buffer
		virtual bool getBuffer(uint32_t*& _pBuffer, int& _iStride) const;
		
		// Release buffer
		virtual void releaseBuffer();

	private:
		// OpenGL texture
		GLuint		m_uTextureID;

		// Texture
		uint32_t*	m_pTextureBuffer;

		// Image width and height
		int			m_iImageWidth;
		int			m_iImageHeight;

		// Texture width and height
		int			m_iTextureWidth;
		int			m_iTextureHeight;

		// Dynamic
		bool		m_bDynamic;

		// Create texture
		bool createTexture(int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic);

		// Lock texture
		bool lockTexture(uint32_t*& _pBuffer, int& _iStride) const;

		// Unlock texture
		bool unlockTexture();

		// Generate texture
		bool generateTexture();

		// Setup texture
		bool setupTexture();
};

ENDNAMESPACE
