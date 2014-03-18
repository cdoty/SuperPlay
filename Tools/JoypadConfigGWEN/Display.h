// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "DirectX9.h"

#define SAFE_RELEASE(p) {if((p)) {(p)->Release(); (p) = NULL;}}

class Display
{
	public:
		// Constructor
		Display();

		// Destructor
		~Display();

		// Create
		static Display* create();

		// Initialize
		bool initialize();
	
		// Close
		void close();
	
		// Initialize DirectX
		bool initializeDirectX(HWND _hWnd);

		// Get device
		LPDIRECT3DDEVICE9 getDevice() const {return m_pDirect3DDevice;}
		
		// Get Direct3D interface
		LPDIRECT3D9 getDirect3D() const {return m_pDirect3D;}

		// Get renderer
		Gwen::Renderer::DirectX9* getRenderer() const {return m_pRenderer;}

	private:
		// Direct 3D interface
		LPDIRECT3D9					m_pDirect3D;
		
		// Direct 3D device
		LPDIRECT3DDEVICE9			m_pDirect3DDevice;

		// Capabilities
		D3DCAPS9					m_direct3DCaps;

		// Gwen renderer
		Gwen::Renderer::DirectX9*	m_pRenderer;

		// Device size
		int							m_iDeviceWidth;
		int							m_iDeviceHeight;
};
