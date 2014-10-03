#pragma once

#ifdef WIN32
#include <windows.h>
#endif

#if defined __APPLE__ 
#include <TargetConditionals.h>
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#define __IOS__
#endif
#endif

#if !defined __ANDROID__ && !defined __IOS__ && !defined MARMALADE && !defined EMSCRIPTEN
#include "GL/glew.h"
#endif

#ifdef __APPLE__
#ifdef __IOS__
#define GL_GLEXT_PROTOTYPES
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#include <OpenGL/gl.h>
#endif
#elif defined __ANDROID__ || defined EMSCRIPTEN
#define GL_GLEXT_PROTOTYPES
#include <GLES/gl.h>
#include <GLES/glext.h>
#elif defined MARMALADE
#else
#include <GL/gl.h>
#endif
#include <TinySTL/vector.h>
#include <TinySTL/unordered_map.h>

#include "IDisplay.h"
#include "IndexBuffer.h"
#include "Macros.h"
#include "Texture.h"
#include "Types.h"
#include "VertexBuffer.h"

#if defined WIN32
#include "GLWin32.h"
#elif defined __ANDROID__
#include "GLAndroid.h"
#elif defined MARMALADE
#include "GLMarmalade.h"
#elif defined EMSCRIPTEN
#include "GLEmscripten.h"
#elif defined __linux__ 
#include "GLLinux.h"
#elif defined __APPLE__ 
#ifdef __IOS__
#include "GLiOS.h"
#else
#include "GLMacOSX.h"
#endif
#endif

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
		virtual bool drawTriangles(int _iVertexBufferIndex, int _iVertices = 0, int _iIndexBufferIndex = -1, 
			int _iTriangles = 0);
		
		// Set clip rect
		virtual void setClipRect(const Rect& _rctClip);

		// Reset clip rect
		virtual void resetClipRect();

#ifdef __IOS__
		// Set default frame buffer
		void setDefaultFrameBuffer(GLuint _uDefaultFrameBuffer) {m_uDefaultFrameBuffer = _uDefaultFrameBuffer;}
#endif

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

		// Render texture UVs
		float		m_fU2;
		float		m_fV2;

		// Frame buffer
		GLuint		m_uFrameBuffer;
		GLuint		m_uRenderTexture;

#ifdef __IOS__
		GLuint		m_uDefaultFrameBuffer;
#endif

		// Vertex buffer
		int			m_iVertexBuffer;
		
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

		// Create render target
		bool createRenderTarget(int _iWidth, int _iHeight, GLint _iFormat = GL_RGBA);
		
		// Create vertex buffer
		bool createVertexBuffer();

		// Setup vertices
		bool setupVertices();

		// Setup transform
		void setupTransform();
};

ENDNAMESPACE
