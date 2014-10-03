// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <math.h>
#include <string.h>

#include "Log.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Utilities.h"

#if defined __APPLE__ 
#include <TargetConditionals.h>
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#define __IOS__
#endif
#endif

NAMESPACE(SPlay)

Texture::Texture()	:
	m_pTextureBuffer(NULL),
	m_uTextureID(GL_INVALID_VALUE),
	m_bDynamic(false)
{
}

Texture::~Texture()
{
	close();
}

bool Texture::create(int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic)
{
	if (false == createTexture(_iWidth, _iHeight, _eFormat, _bDynamic))
	{
		return	false;
	}
	
	return	true;
}

void Texture::close()
{
	delete[]	m_pTextureBuffer;

	m_pTextureBuffer	= NULL;

	if (m_uTextureID != GL_INVALID_VALUE)
	{
		glDeleteTextures(1, &m_uTextureID);

		m_uTextureID	= GL_INVALID_VALUE;
	}
}

void Texture::getSize(int& _iTextureWidth, int& _iTextureHeight) const
{
	_iTextureWidth	= m_iTextureWidth;
	_iTextureHeight	= m_iTextureHeight;
}

bool Texture::getBuffer(uint32_t*& _pBuffer, int& _iStride) const
{
	return	lockTexture(_pBuffer, _iStride);
}

void Texture::releaseBuffer()
{
	unlockTexture();
}

bool Texture::createTexture(int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic)
{
	m_iImageWidth	= _iWidth;
	m_iImageHeight	= _iHeight;
	m_bDynamic		= _bDynamic;

	m_iTextureWidth		= static_cast<int>(pow(2, ceil(Utilities::log2(m_iImageWidth))));
	m_iTextureHeight	= static_cast<int>(pow(2, ceil(Utilities::log2(m_iImageHeight))));

	int	iMaxTextureSize;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &iMaxTextureSize);

	if (_iWidth > iMaxTextureSize || _iHeight > iMaxTextureSize)
	{
		Log::instance()->logError("OpenGL cannot create a texture bigger than %d pixels", iMaxTextureSize);

		return	false;
	}

	int	iTextureSize	= m_iTextureWidth * m_iTextureHeight;

	m_pTextureBuffer	= new uint32_t[iTextureSize];

	memset(m_pTextureBuffer, 0, iTextureSize * sizeof(uint32_t));

	m_uTextureID	= 0;

	if (false == generateTexture())
	{
		return	false;
	}

	if (false == setupTexture())
	{
		return	false;
	}

	return	true;
}
	 
bool Texture::lockTexture(uint32_t*& _pBuffer, int& _iStride) const
{
	_pBuffer	= m_pTextureBuffer;
	_iStride	= m_iTextureWidth;

	return	true;
}

bool Texture::unlockTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_uTextureID);

#if defined __IOS__
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_iImageWidth, m_iImageHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_pTextureBuffer);
#else
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_iImageWidth, m_iImageHeight, GL_RGBA, GL_UNSIGNED_BYTE, m_pTextureBuffer);
#endif

	return	true;
}

bool Texture::generateTexture()
{
	glGenTextures(1, &m_uTextureID);

	GLenum	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create texture %d", error);

		return	false;
	}

	glBindTexture(GL_TEXTURE_2D, m_uTextureID);

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to bind texture %d", error);

		return	false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return	true;
}

bool Texture::setupTexture()
{
#if defined __IOS__
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iTextureWidth, m_iTextureHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_pTextureBuffer);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iTextureWidth, m_iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pTextureBuffer);
#endif

	GLenum	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to setup texture %d", error);

		return	false;
	}

	return	true;
}

ENDNAMESPACE
