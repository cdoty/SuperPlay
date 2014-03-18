// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <math.h>

#include "Display.h"
#include "Log.h"
#include "System.h"
#include "PlatformDefines.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Utilities.h"

NAMESPACE(SPlay)

Texture::Texture()	:
	m_pTexture(NULL),
	m_bDynamic(false)
{
}

Texture::~Texture()
{
	close();
}

bool Texture::create(LPDIRECT3DDEVICE9 _pD3DDevice, int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic)
{
	if (false == createTexture(_pD3DDevice, _iWidth, _iHeight, _eFormat, _bDynamic))
	{
		return	false;
	}
	
	return	true;
}

void Texture::close()
{
	SAFE_RELEASE(m_pTexture);
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

bool Texture::createTexture(LPDIRECT3DDEVICE9 _pD3DDevice, int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic)
{
	m_iImageWidth	= _iWidth;
	m_iImageHeight	= _iHeight;
	m_bDynamic		= _bDynamic;

	m_iTextureWidth		= static_cast<int>(pow(2, ceil(Utilities::log2(m_iImageWidth))));
	m_iTextureHeight	= static_cast<int>(pow(2, ceil(Utilities::log2(m_iImageHeight))));

	Display* pDisplay	= static_cast<Display*>(System::getDisplay());

	int	iMaxTextureWidth	= pDisplay->getMaxTextureWidth();
	int	iMaxTextureHeight	= pDisplay->getMaxTextureHeight();

	if (m_iTextureWidth > iMaxTextureWidth || m_iTextureHeight > iMaxTextureHeight)
	{
		Log::instance()->logError("DirectX cannot create a texture bigger than %d %d", iMaxTextureWidth, iMaxTextureHeight);

		return	false;
	}

	HRESULT	hResult	= _pD3DDevice->CreateTexture(m_iTextureWidth, m_iTextureHeight, 1, m_bDynamic ? D3DUSAGE_DYNAMIC : 0, 
		(NoAlpha == _eFormat) ? D3DFMT_X8R8G8B8 : D3DFMT_A8R8G8B8, m_bDynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED, &m_pTexture, NULL);

	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateTexture error (%08X)", hResult);

		return	false;
	}

	return	true;
}
	 
bool Texture::lockTexture(uint32_t*& _pBuffer, int& _iStride) const
{
	D3DLOCKED_RECT	lockedRect;

	HRESULT	hResult	= m_pTexture->LockRect(0, &lockedRect, NULL, (true == m_bDynamic) ? D3DLOCK_DISCARD : 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Unable to lock texture");

		return	false;
	}

	_iStride	= lockedRect.Pitch / sizeof(uint32_t);
	_pBuffer	= static_cast<uint32_t*>(lockedRect.pBits);

	return	true;
}

bool Texture::unlockTexture()
{
	HRESULT	hResult	= m_pTexture->UnlockRect(0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("UnlockRect error (%08X)", hResult);
		
		return	false;
	}

	return	true;
}

ENDNAMESPACE
