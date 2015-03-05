#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <TinySTL/vector.h>
#include <TinySTL/unordered_map.h>

#include "GLPlatform.h"
#include "IDisplay.h"
#include "IndexBuffer.h"
#include "Macros.h"
#include "PlatformDefines.h"
#include "Texture.h"
#include "Types.h"
#include "VertexBuffer.h"

NAMESPACE(SPlay)

class Display : public IDisplay
{
	public:
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

	private:
		struct TextureData
		{
			Texture*	pTexture;
			int			iReferenceCount;
		};

		// GL platform
		GLPlatform*	m_pGLPlatform;

		// Window size
		float		m_fRenderWidth;
		float		m_fRenderHeight;

#if !SCALED_DISPLAY
		// Frame buffer
		GLuint		m_uFrameBuffer;
		GLuint		m_uRenderTexture;

		// Vertex buffer
		int			m_iVertexBuffer;
#endif
		
		// Dynamic textures supported?
		bool		m_bDynamicTextures;

		typedef	tinystl::unordered_map<size_t, TextureData> TextureMap;

		// Textures
		TextureMap	m_mapTextures;

		// Vertex buffers
		tinystl::vector<VertexBuffer*>	m_vecVertexBuffers;

		// Index buffers
		tinystl::vector<IndexBuffer*>	m_vecIndexBuffers;

		// Offset
		Point		m_ptOffset;
		
		// Initialize OpenGL
		bool initializeOpenGL();

		// Close OpenGL
		void closeOpenGL();

		// Setup device
		bool setupDevice();

#if !SCALED_DISPLAY
		// Create render target
		bool createRenderTarget(int _iWidth, int _iHeight, GLint _iFormat = GL_RGBA);
		
		// Create vertex buffer
		bool createVertexBuffer();

		// Setup vertices
		bool setupVertices();
#endif
		
		// Setup transform
		void setupTransform();
};

ENDNAMESPACE
