// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include "AssertLog.h"
#include "Defines.h"
#include "Display.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

Display::Display()	:
	m_pDirect3D(NULL),
	m_pDirect3DDevice(NULL),
	m_pRenderer(NULL)
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
	m_iDeviceWidth	= gsc_iWindowWidth;
	m_iDeviceHeight	= gsc_iWindowHeight;

	// Create a NULL renderer. The renderer will be created after the window is created.
	m_pRenderer = new Gwen::Renderer::DirectX9(NULL);

	return	true;
}

void Display::close()
{
	delete	m_pRenderer;
	
	m_pRenderer	= NULL;

	m_pDirect3DDevice	= NULL;

	SAFE_RELEASE(m_pDirect3D);
}

bool Display::initializeDirectX(HWND _hWnd)
{
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

	D3DPRESENT_PARAMETERS	presentParameters;
	
	memset(&presentParameters, 0, sizeof(D3DPRESENT_PARAMETERS));

	presentParameters.BackBufferFormat			= displayMode.Format;
	presentParameters.BackBufferCount			= 1;
	presentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	presentParameters.Windowed					= TRUE;
	presentParameters.EnableAutoDepthStencil	= FALSE;
	presentParameters.AutoDepthStencilFormat	= D3DFMT_D16;
	presentParameters.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;
	presentParameters.hDeviceWindow				= _hWnd;

	hResult	= m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, uBehaviorFlags, &presentParameters, &m_pDirect3DDevice);
	
	if (FAILED(hResult))
	{
		Log::instance()->logError("CreateDevice error (%08X)", hResult);

		return	false;
	}

	// Set the final device device
	m_pRenderer->setDevice(m_pDirect3DDevice);

	return	true;
}
