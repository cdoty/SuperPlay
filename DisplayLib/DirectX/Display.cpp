// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "Display.h"
#include "GameHeader.h"
#include "Hardware.h"
#include "CustomVertex.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Utilities.h"

#ifdef _DEBUG
//#define	D3D_DEBUG_INFO
#endif

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

NAMESPACE(SPlay)

IDisplay* createDisplay()
{
	return	Display::create();
}

Display::Display()	:
	m_pDirect3D(NULL),
	m_pDirect3DDevice(NULL),
	m_pRenderTexture(NULL),
	m_pOffscreenSurface(NULL),
	m_iVertexBuffer(-1)
{
}

Display::~Display()
{
	close();
}

Display* Display::create()
{
	Display*	pDisplay	= new Display();

	if (false == pDisplay->initialize())
	{
		delete	pDisplay;

		pDisplay	= NULL;
	}

	return	pDisplay;
}

bool Display::initialize()
{
	m_iDeviceWidth	= Platform::getWindow()->getWindowWidth();
	m_iDeviceHeight	= Platform::getWindow()->getWindowHeight();

	if (false == initializeDirectX())
	{
		return	false;
	}
	
	return	true;
}

void Display::close()
{
	SAFE_RELEASE(m_pOffscreenSurface);
	SAFE_RELEASE(m_pRenderTexture);
	SAFE_RELEASE(m_pDirect3DDevice);
	SAFE_RELEASE(m_pDirect3D);
		
	int	t_c	= m_vecVertexBuffers.size();
	
	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete	m_vecVertexBuffers[iLoop];
		
		m_vecVertexBuffers[iLoop]	= NULL;
	}
	
	m_vecVertexBuffers.clear();

	t_c	= m_vecIndexBuffers.size();
	
	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete	m_vecIndexBuffers[iLoop];
		
		m_vecIndexBuffers[iLoop]	= NULL;
	}
	
	m_vecIndexBuffers.clear();
}

bool Display::render()
{
	const GameHeader&	gameHeader	= System::getGameHeader();

	if (true == gameHeader.bFramedWindow && false == gameHeader.bFullScreen)
	{
		return	renderFramed();
	}

	return	renderNormal();
}

void Display::clear(uint32_t _uColor)
{
	m_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, _uColor, 1.0f, 0);
}

void Display::resize()
{
	setupTransform();
	setupVertices();

	D3DXMatrixOrthoOffCenterLH(&m_ortho2D, 0.0f, static_cast<float>(m_fRenderWidth), static_cast<float>(m_fRenderHeight), 0.0f, 0.0f, 1.0f);
}

int Display::createVertexBuffer(int _iVertices, bool _bDynamic)
{
	VertexBuffer*	pVertexBuffer	= new VertexBuffer();

	if (false == pVertexBuffer->create(m_pDirect3DDevice, _iVertices, _bDynamic))
	{
		delete	pVertexBuffer;

		return	-1;
	}

	int	iIndex	= m_vecVertexBuffers.size();

	m_vecVertexBuffers.push_back(pVertexBuffer);

	return	iIndex;
}

VertexBuffer* Display::getVertexBuffer(int _iIndex) const
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < static_cast<int>(m_vecVertexBuffers.size()), "Vertex buffer index is invalid.\n");

	return	m_vecVertexBuffers[_iIndex];
}

void Display::removeVertexBuffer(int _iIndex)
{
	delete	m_vecVertexBuffers[_iIndex];
		
	m_vecVertexBuffers[_iIndex]	= NULL;
}

int Display::createIndexBuffer(int _iVertices, bool _bDynamic)
{
	IndexBuffer*	pIndexBuffer	= new IndexBuffer();

	if (false == pIndexBuffer->create(m_pDirect3DDevice, _iVertices, _bDynamic))
	{
		delete	pIndexBuffer;

		return	-1;
	}

	int	iIndex	= m_vecIndexBuffers.size();

	m_vecIndexBuffers.push_back(pIndexBuffer);

	return	iIndex;
}

IndexBuffer* Display::getIndexBuffer(int _iIndex) const
{
	ASSERT_LOG(_iIndex >= 0 && _iIndex < static_cast<int>(m_vecVertexBuffers.size()), "Vertex buffer index is invalid.\n");

	return	m_vecIndexBuffers[_iIndex];
}

void Display::removeIndexBuffer(int _iIndex)
{
	delete	m_vecIndexBuffers[_iIndex];
		
	m_vecIndexBuffers[_iIndex]	= NULL;
}

int Display::createTexture(const char* _szTextureName, int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic)
{
	int	iHash	= Utilities::getHash(_szTextureName);

	if (m_mapTextures.find(iHash) == m_mapTextures.end())
	{
		Texture*	pTexture	= new Texture();

		if (false == pTexture->create(m_pDirect3DDevice, _iWidth, _iHeight, _eFormat, false == m_bDynamicTextures ? false : _bDynamic))
		{
			delete	pTexture;

			return	-1;
		}

		TextureData	textureData;

		textureData.pTexture		= pTexture;
		textureData.iReferenceCount	= 1;

		m_mapTextures[iHash]		= textureData;
	}
	
	else
	{
		m_mapTextures[iHash].iReferenceCount++;
	}

	return	iHash;
}

Texture* Display::getTexture(int _iHash)
{
	if (m_mapTextures.find(_iHash) == m_mapTextures.end())
	{
		return	NULL;
	}
	
	return	m_mapTextures[_iHash].pTexture;
}

void Display::removeTexture(int _iHash)
{
	TextureMap::const_iterator	itFound	= m_mapTextures.find(_iHash);

	if (itFound != m_mapTextures.end())
	{
		m_mapTextures[_iHash].iReferenceCount--;
		
		if (m_mapTextures[_iHash].iReferenceCount <= 0)
		{
			delete	m_mapTextures[_iHash].pTexture;
			
			m_mapTextures.erase(itFound);
		}
	}
}

void Display::bindTexture(int _iHash)
{
	// Set texture stage settings
	HRESULT	hResult	= m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTextureStageState error (%08X)", hResult);

		return;
	}

	hResult	= m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTextureStageState error (%08X)", hResult);

		return;
	}

	hResult	= m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTextureStageState error (%08X)", hResult);

		return;
	}

	hResult	= m_pDirect3DDevice->SetTexture(0, m_mapTextures[_iHash].pTexture->getTexture());

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTexture error (%08X)", hResult);

		return;
	}
}

bool Display::drawTriangles(int _iVertexBufferIndex, int _iVertices, int _iIndexBufferIndex, int _iTriangles)
{
	ASSERT_LOG(_iVertexBufferIndex >= 0 && _iVertexBufferIndex < static_cast<int>(m_vecVertexBuffers.size()),
		"Vertex buffer index is invalid.\n");
	
	ASSERT_LOG(_iIndexBufferIndex >= 0 && _iIndexBufferIndex < static_cast<int>(m_vecIndexBuffers.size()),
		"Index buffer index is invalid.\n");

	VertexBuffer*	pVertices	= m_vecVertexBuffers[_iVertexBufferIndex];

	HRESULT	hResult	= m_pDirect3DDevice->SetStreamSource(0, pVertices->getVertexBuffer(), 0, sizeof(CustomVertex));

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetStreamSource error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->SetFVF(VertexFormat);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("SetFVF error (%08X)", hResult);

		return	false;
	}

	if (0 == _iVertices)
	{
		_iVertices	= pVertices->getVertexCount();
	}

	if (_iIndexBufferIndex != -1)
	{
		IndexBuffer*	pIndices	= m_vecIndexBuffers[_iIndexBufferIndex];

		if (0 == _iTriangles)
		{
			_iTriangles	= pIndices->getIndexCount() - 2;
		}
		
		hResult	= m_pDirect3DDevice->SetIndices(pIndices->getIndexBuffer());

		if (FAILED(hResult))
		{
			Log::instance()->logError("SetIndices error (%08X)", hResult);

			return	false;
		}

		hResult	= m_pDirect3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _iVertices, 0, _iTriangles);

		if (FAILED(hResult))
		{
			Log::instance()->logError("DrawIndexedPrimitive error (%08X)", hResult);

			return	false;
		}
	}
	
	else
	{
		hResult	= m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _iVertices);

		if (FAILED(hResult))
		{
			Log::instance()->logError("DrawPrimitive error (%08X)", hResult);

			return	false;
		}
	}
	
	return	true;
}

void Display::setClipRect(const Rect& _rctClip)
{
	RECT	rect;

	rect.left	= _rctClip.iLeft;
	rect.top	= _rctClip.iTop;
	rect.right	= _rctClip.right();
	rect.bottom	= _rctClip.bottom();

	m_pDirect3DDevice->SetScissorRect(&rect);

	// Enable scissor test
	m_pDirect3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
}

void Display::resetClipRect()
{
	// Disable scissor test
	m_pDirect3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
}

bool Display::initializeDirectX()
{
	HWND	hWnd	= Platform::getWindow()->getHwnd();
	
	m_pDirect3D	= Direct3DCreate9(D3D_SDK_VERSION);

	if (NULL == m_pDirect3D)
	{
		return	false;
	}

	D3DDISPLAYMODE	displayMode;

	HRESULT	hResult	= m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	if (FAILED(hResult))
	{
		Log::instance()->logError("GetAdapterDisplayMode error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displayMode.Format, D3DUSAGE_DEPTHSTENCIL, 
		D3DRTYPE_SURFACE, D3DFMT_D16);
	
	if (FAILED(hResult) && D3DERR_NOTAVAILABLE == hResult)
	{
		return	false;
	}

	hResult	= m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_direct3DCaps);

	if (FAILED(hResult))
	{
		Log::instance()->logError("GetDeviceCaps error (%08X)", hResult);

		return	false;
	}

	DWORD uBehaviorFlags;

	if (m_direct3DCaps.VertexProcessingCaps != 0)
	{
		uBehaviorFlags	= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	else
	{
		uBehaviorFlags	= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (m_direct3DCaps.Caps2 & D3DCAPS2_DYNAMICTEXTURES)
	{
		m_bDynamicTextures	= true;
	}

	else
	{
		m_bDynamicTextures	= false;
	}

	D3DPRESENT_PARAMETERS	presentParameters;
	
	memset(&presentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));

	const GameHeader&	gameHeader	= System::getGameHeader();

	if (true == gameHeader.bFullScreen)
	{
		presentParameters.BackBufferFormat	= D3DFMT_X8R8G8B8;
		presentParameters.BackBufferWidth	= m_iDeviceWidth;
		presentParameters.BackBufferHeight	= Platform::getWindow()->getWindowHeight(); 
	}

	else
	{
		presentParameters.BackBufferFormat		= displayMode.Format;
	}

	presentParameters.BackBufferCount			= 1;
	presentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	presentParameters.Windowed					= true == gameHeader.bFullScreen ? FALSE : TRUE;
	presentParameters.EnableAutoDepthStencil	= FALSE;
	presentParameters.AutoDepthStencilFormat	= D3DFMT_D16;
	presentParameters.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;
	presentParameters.hDeviceWindow				= Platform::getWindow()->getHwnd();

	hResult	= m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, uBehaviorFlags, &presentParameters, 
		&m_pDirect3DDevice);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateDevice error (%08X)", hResult);

		return	false;
	}

	// Setup device
	if (false == setupDevice())
	{
		return	false;
	}

	// Create render target
	if (false == createRenderTarget(gameHeader.iScreenWidth, gameHeader.iScreenHeight))
	{
		return	false;
	}
	
	// Create offscreen surface
	if (false == createOffscreenSurface())
	{
		return	false;
	}

	return	true;
}

bool Display::setupDevice()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	D3DXMatrixOrthoOffCenterLH(&m_ortho2D, 0.0f, static_cast<float>(m_iDeviceWidth), static_cast<float>(m_iDeviceHeight), 0.0f, 0.0f, 1.0f);

	D3DXMatrixIdentity(&m_identity);

	HRESULT	hResult	= m_pDirect3DDevice->SetTransform(D3DTS_WORLD, &m_identity);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTransform error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->SetTransform(D3DTS_VIEW, &m_identity);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTransform error (%08X)", hResult);

		return	false;
	}

	// Set render states
	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}

	// Disable lighting
	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}

	// Disable z-buffer
	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}

	// Enable alpha blending
	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}

   	// Set alpha blend parameters
	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}
   	
	hResult	= m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderState error (%08X)", hResult);

		return	false;
	}
   	
   	// Setup texture filtering
	hResult	= m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetSamplerState error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetSamplerState error (%08X)", hResult);

		return	false;
	}

	// Set textute UV mapping
	hResult	= m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetSamplerState error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetSamplerState error (%08X)", hResult);

		return	false;
	}

	return	true;
}

bool Display::createRenderTarget(int _iWidth, int _iHeight, D3DFORMAT _eFormat)
{
	m_fRenderTextureWidth	= static_cast<float>(_iWidth);
	m_fRenderTextureHeight	= static_cast<float>(_iHeight);

	int	iTextureWidth		= static_cast<int>(pow(2, ceil(Utilities::log2(_iWidth))));
	int	iTextureHeight		= static_cast<int>(pow(2, ceil(Utilities::log2(_iHeight))));

	if (iTextureWidth > static_cast<int>(m_direct3DCaps.MaxTextureWidth) || 
		iTextureHeight > static_cast<int>(m_direct3DCaps.MaxTextureHeight))
	{
		return	false;
	}
	
	m_fEdgeU	= m_fRenderTextureWidth / static_cast<float>(iTextureWidth);
	m_fEdgeV	= m_fRenderTextureHeight / static_cast<float>(iTextureHeight);

	HRESULT	hResult	= m_pDirect3DDevice->CreateTexture(iTextureWidth, iTextureHeight, 1, D3DUSAGE_RENDERTARGET, _eFormat, D3DPOOL_DEFAULT, 
		&m_pRenderTexture, NULL);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateTexture error (%08X)", hResult);

		return	false;
	}
	
	if (false == createVertexBuffer())
	{
		return	false;
	}

	D3DXMatrixOrthoOffCenterLH(&m_renderTarget, 0.0f, m_fRenderTextureWidth, m_fRenderTextureHeight, 0.0f, 0.0f, 1.0f);

	m_iRenderTextureWidth	= iTextureWidth;
	m_iRenderTextureHeight	= iTextureHeight;

	return	true;
}

bool Display::createOffscreenSurface()
{
	HRESULT	hResult	= m_pDirect3DDevice->CreateOffscreenPlainSurface((UINT)m_iRenderTextureWidth, (UINT)m_iRenderTextureHeight, D3DFMT_A8R8G8B8, 
		D3DPOOL_SYSTEMMEM, &m_pOffscreenSurface, 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateOffscreenPlainSurface error (%08X)", hResult);

		return	false;
	}

	return	true;
}

bool Display::createVertexBuffer()
{
	setupTransform();

	m_iVertexBuffer	= createVertexBuffer(4, false);

	if (-1 == m_iVertexBuffer)
	{
		return	false;
	}

	if (false == setupVertices())
	{
		return	false;
	}

	return	true;
}

bool Display::setupVertices()
{
	VertexBuffer*	pVertexBuffer	= getVertexBuffer(m_iVertexBuffer);

	int	iVertices;
	
	CustomVertex*	pBuffer	= static_cast<CustomVertex*>(pVertexBuffer->getBuffer(iVertices));

	float	fOffsetX	= static_cast<float>(m_ptOffset.iX) - 0.5f;
	float	fOffsetY	= static_cast<float>(m_ptOffset.iY) - 0.5f;

	int	iIndex	= 0;

	pBuffer[iIndex].fX	= fOffsetX;
	pBuffer[iIndex].fY	= fOffsetY;
	pBuffer[iIndex].fZ	= 0.0f;
	pBuffer[iIndex].fW	= 1.0f;

	pBuffer[iIndex].fU	= 0.0;
	pBuffer[iIndex].fV	= 0.0;
	
	iIndex++;

	pBuffer[iIndex].fX	= fOffsetX + m_fRenderWidth;
	pBuffer[iIndex].fY	= fOffsetY;
	pBuffer[iIndex].fZ	= 0.0f;
	pBuffer[iIndex].fW	= 1.0f;

	pBuffer[iIndex].fU	= m_fEdgeU;
	pBuffer[iIndex].fV	= 0.0f;
	
	iIndex++;

	pBuffer[iIndex].fX	= fOffsetX;
	pBuffer[iIndex].fY	= fOffsetY + m_fRenderHeight;
	pBuffer[iIndex].fZ	= 0.0f;
	pBuffer[iIndex].fW	= 1.0f;

	pBuffer[iIndex].fU	= 0.0f;
	pBuffer[iIndex].fV	= m_fEdgeV;
	
	iIndex++;

	pBuffer[iIndex].fX	= fOffsetX + m_fRenderWidth;
	pBuffer[iIndex].fY	= fOffsetY + m_fRenderHeight;
	pBuffer[iIndex].fZ	= 0.0f;
	pBuffer[iIndex].fW	= 1.0f;

	pBuffer[iIndex].fU	= m_fEdgeU;
	pBuffer[iIndex].fV	= m_fEdgeV;

	pVertexBuffer->releaseBuffer();

	return	true;
}

void Display::setupTransform()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	float	fScreenWidth	= static_cast<float>(gameHeader.iScreenWidth);
	float	fScreenHeight	= static_cast<float>(gameHeader.iScreenHeight);
	float	fScaleX			= static_cast<float>(gameHeader.iWindowedWidth) / fScreenWidth;
	float	fScaleY			= static_cast<float>(gameHeader.iWindowedHeight) / fScreenHeight;
	
	m_ptOffset.iX	= 0;
	m_ptOffset.iY	= 0;

	float	fScale;

	if (fScaleX >= fScaleY)
	{
		m_ptOffset.iX	= (gameHeader.iWindowedWidth - static_cast<int>(fScreenWidth * fScaleY)) / 2;

		fScale	= fScaleY;
	}
	
	else
	{
		m_ptOffset.iY	= (gameHeader.iWindowedHeight - static_cast<int>(fScreenHeight * fScaleX)) / 2;

		fScale	= fScaleX;
	}

	m_fRenderWidth	= fScreenWidth * fScale;
	m_fRenderHeight	= fScreenHeight * fScale;
}

bool Display::renderFramed()
{
	Window*	pWindow	= Platform::getWindow();

	uint8_t*	pLayeredBuffer	= pWindow->getLayeredBuffer();
	int			iLayeredWidth	= pWindow->getLayeredWidth();
	int			iLayeredHeight	= pWindow->getLayeredHeight();
	
	LPDIRECT3DSURFACE9	pBackBuffer		= NULL;
	LPDIRECT3DSURFACE9	pRenderSurface	= NULL;

	HRESULT	hResult	= m_pDirect3DDevice->GetRenderTarget(0, &pBackBuffer);

	if (FAILED(hResult))
	{
		Log::instance()->logError("GetRenderTarget error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pRenderTexture->GetSurfaceLevel(0, &pRenderSurface);

	if (FAILED(hResult))
	{
		Log::instance()->logError("GetSurfaceLevel error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetRenderTarget(0, pRenderSurface);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderTarget error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetTransform(D3DTS_PROJECTION, &m_renderTarget);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTransform error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->BeginScene();

	if (FAILED(hResult))
	{
		Log::instance()->logError("BeginScene error (%08X)", hResult);

		return	false;
	}

	// Render the hardware view
	Hardware::render();

	hResult	= m_pDirect3DDevice->EndScene();

	if (FAILED(hResult))
	{
		Log::instance()->logError("EndScene error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->GetRenderTargetData(pRenderSurface, m_pOffscreenSurface);

	if (SUCCEEDED(hResult))
	{
		D3DLOCKED_RECT	lockedRect	= {0};

		hResult	= m_pOffscreenSurface->LockRect(&lockedRect, 0, 0);

		if (SUCCEEDED(hResult))
		{
			const uint8_t*	pSrc	= (const uint8_t*)lockedRect.pBits;

			if (m_iRenderTextureWidth == iLayeredWidth && m_iRenderTextureHeight == iLayeredHeight)
			{
				memcpy(pLayeredBuffer, pSrc, (int)(m_fRenderTextureWidth * m_fRenderTextureHeight * 4));
			}

			else
			{
				int	iBufferWidth	= iLayeredWidth * 4;
				int	iStride			= lockedRect.Pitch;

				uint8_t*	pDest	= pLayeredBuffer;

				for (int iYLoop = 0; iYLoop < iLayeredHeight; ++iYLoop)
				{
					memcpy(pDest, pSrc, iBufferWidth);
					
					pDest	+= iBufferWidth;
					pSrc	+= iStride;
				}
			}
			m_pOffscreenSurface->UnlockRect();
		}
	}

	m_pDirect3DDevice->SetRenderTarget(0, pBackBuffer);

	SAFE_RELEASE(pRenderSurface);
	SAFE_RELEASE(pBackBuffer);

	return	true;
}

bool Display::renderNormal()
{
	LPDIRECT3DSURFACE9	pBackBuffer		= NULL;
	LPDIRECT3DSURFACE9	pRenderSurface	= NULL;

	HRESULT	hResult	= m_pDirect3DDevice->GetRenderTarget(0, &pBackBuffer);

	if (FAILED(hResult))
	{
		Log::instance()->logError("GetRenderTarget error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pRenderTexture->GetSurfaceLevel(0, &pRenderSurface);

	if (FAILED(hResult))
	{
		Log::instance()->logError("GetSurfaceLevel error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetRenderTarget(0, pRenderSurface);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderTarget error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetTransform(D3DTS_PROJECTION, &m_renderTarget);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTransform error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->BeginScene();

	if (FAILED(hResult))
	{
		Log::instance()->logError("BeginScene error (%08X)", hResult);

		return	false;
	}

	// Render the hardware view
	Hardware::render();

	hResult	= m_pDirect3DDevice->EndScene();

	if (FAILED(hResult))
	{
		Log::instance()->logError("EndScene error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetRenderTarget(0, pBackBuffer);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetRenderTarget error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetTransform(D3DTS_PROJECTION, &m_ortho2D);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTransform error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->BeginScene();

	if (FAILED(hResult))
	{
		Log::instance()->logError("BeginScene error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0);

	if (FAILED(hResult))
	{
		Log::instance()->logError("Clear error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetTexture(0, m_pRenderTexture);

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetTexture error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetStreamSource(0, getVertexBuffer(m_iVertexBuffer)->getVertexBuffer(), 0, sizeof(CustomVertex));

	if (FAILED(hResult))
	{
		Log::instance()->logError("SetStreamSource error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->SetFVF(VertexFormat);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("SetFVF error (%08X)", hResult);

		return	false;
	}

	hResult	= m_pDirect3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (FAILED(hResult))
	{
		Log::instance()->logError("DrawPrimitive error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->EndScene();

	if (FAILED(hResult))
	{
		Log::instance()->logError("EndScene error (%08X)", hResult);

		return	false;
	}
	
	hResult	= m_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

	if (FAILED(hResult))
	{
//		Log::instance()->logError("Present error (%08X)", hResult);

		return	false;
	}
	
	SAFE_RELEASE(pRenderSurface);
	SAFE_RELEASE(pBackBuffer);

	return	true;
}

ENDNAMESPACE
