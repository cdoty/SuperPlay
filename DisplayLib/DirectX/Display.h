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
#include <TinySTL\vector.h>
#include <TinySTL\unordered_map.h>

#include "IDisplay.h"
#include "IndexBuffer.h"
#include "Macros.h"
#include "Texture.h"
#include "Types.h"
#include "VertexBuffer.h"
#include "Window.h"

NAMESPACE(SPlay)

class Display : public IDisplay
{
	public:
		enum FVFData
		{
			VertexFormat	= D3DFVF_XYZRHW | D3DFVF_TEX1
		};

		// Constructor
		Display();

		// Destructor
		virtual ~Display();

		// Create
		static Display* create();

		// Initialize
		virtual bool initialize();
	
		// Close
		virtual void close();
	
		// Render
		virtual bool render();

		// Clear
		virtual void clear(uint32_t _uColor);

		// Resize
		virtual void resize();

		// Get device
		LPDIRECT3DDEVICE9 getDevice() const {return m_pDirect3DDevice;}
		
		// Get Direct3D interface
		LPDIRECT3D9 getDirect3D() const {return m_pDirect3D;}
		
		// Create vertex buffer
		virtual int createVertexBuffer(int _iVertices, bool _bDynamic);

		// Get vertex buffer
		virtual VertexBuffer* getVertexBuffer(int _iIndex) const;

		// Remove vertex buffer
		virtual void removeVertexBuffer(int _iIndex);

		// Create index buffer
		virtual int createIndexBuffer(int _iVertices, bool _bDynamic);

		// Get index buffer
		virtual IndexBuffer* getIndexBuffer(int _iIndex) const;

		// Remove index buffer
		virtual void removeIndexBuffer(int _iIndex);

		// Create texture
		virtual int createTexture(const char* _szTextureName, int _iWidth, int _iHeight, eFormat _eFormat, bool _bDynamic);
		
		// Get texture
		virtual Texture* getTexture(int _iHash);

		// Remove texture
		virtual void removeTexture(int _iHash);

		// Bind texture
		virtual void bindTexture(int _iHash);

		// Draw triangles
		virtual bool drawTriangles(int _iVertexBufferIndex, int _iVertices = 0, int _iIndexBufferIndex = -1, int _iTriangles = 0);
		
		// Set clip rect
		virtual void setClipRect(const Rect& _rctClip);

		// Reset clip rect
		virtual void resetClipRect();

		// Get max texture size
		int getMaxTextureWidth() const {return m_direct3DCaps.MaxTextureWidth;}
		int getMaxTextureHeight() const {return m_direct3DCaps.MaxTextureHeight;}

	private:
		struct TextureData
		{
			Texture*	pTexture;
			int			iReferenceCount;
		};

		// Direct 3D interface
		LPDIRECT3D9				m_pDirect3D;
		
		// Direct 3D device
		LPDIRECT3DDEVICE9		m_pDirect3DDevice;

		// Render target texture
		LPDIRECT3DTEXTURE9		m_pRenderTexture;
		
		// Device size
		int						m_iDeviceWidth;
		int						m_iDeviceHeight;

		// Render texture size
		float					m_fRenderTextureWidth;
		float					m_fRenderTextureHeight;

		// Render texture UV
		float					m_fEdgeU;
		float					m_fEdgeV;

		// Window size
		float					m_fRenderWidth;
		float					m_fRenderHeight;

		// Vertex buffer
		int						m_iVertexBuffer;

		// Matrices
		D3DXMATRIX				m_ortho2D;	
		D3DXMATRIX				m_renderTarget;	
		D3DXMATRIX				m_identity;

		// Capabilities
		D3DCAPS9				m_direct3DCaps;

		// Dynamic textures supported?
		bool					m_bDynamicTextures;

		typedef	tinystl::unordered_map<size_t, TextureData> TextureMap;

		// Textures
		TextureMap	m_mapTextures;

		// Vertex buffers
		tinystl::vector<VertexBuffer*>	m_vecVertexBuffers;

		// Index buffers
		tinystl::vector<IndexBuffer*>	m_vecIndexBuffers;

		// Offset
		Point	m_ptOffset;
		
		// Initialize DirectX
		bool initializeDirectX();

		// Setup device
		bool setupDevice();

		// Create render target
		bool createRenderTarget(int _iWidth, int _iHeight, D3DFORMAT _eFormat = D3DFMT_A8R8G8B8);
		
		// Create vertex buffer
		bool createVertexBuffer();

		// Setup vertices
		bool setupVertices();

		// Setup transform
		void setupTransform();
};

ENDNAMESPACE
