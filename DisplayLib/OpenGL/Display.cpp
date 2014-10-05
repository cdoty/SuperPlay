#include <math.h>

#include "AssertLog.h"
#include "Display.h"
#include "GameHeader.h"
#include "Hardware.h"
#include "CustomVertex.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Utilities.h"

#ifdef __IOS__
//#define USE_16BIT
#endif

NAMESPACE(SPlay)

IDisplay* createDisplay()
{
	return	Display::create();
}

Display::Display()	:
	m_pGLPlatform(NULL),
	m_uFrameBuffer(GL_INVALID_VALUE),
	m_uRenderTexture(0),
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
	m_pGLPlatform	= GLPlatform::create();

	if (NULL == m_pGLPlatform)
	{
		return	false;
	}

	if (false == initializeOpenGL())
	{
		return	false;
	}

	return	true;
}

void Display::close()
{
	if (m_uFrameBuffer != GL_INVALID_VALUE)
	{
#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
		glDeleteFramebuffersOES(1, &m_uFrameBuffer);
#else
		if (GLEW_ARB_framebuffer_object)
		{
			glDeleteFramebuffers(1, &m_uFrameBuffer);
		}

		else if (GLEW_EXT_framebuffer_object)
		{
			glDeleteFramebuffersEXT(1, &m_uFrameBuffer);
		}
#endif
		
		m_uFrameBuffer	= GL_INVALID_VALUE;
	}
		
	closeOpenGL();

	delete	m_pGLPlatform;

	m_pGLPlatform	= NULL;

	int	t_c	= static_cast<int>(m_vecVertexBuffers.size());
	
	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		delete	m_vecVertexBuffers[iLoop];
		
		m_vecVertexBuffers[iLoop]	= NULL;
	}
	
	m_vecVertexBuffers.clear();

	t_c	= static_cast<int>(m_vecIndexBuffers.size());
	
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

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uFrameBuffer);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBuffer);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER, m_uFrameBuffer);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, gameHeader.iScreenWidth, gameHeader.iScreenHeight);

	// Reset project matrix
	glMatrixMode(GL_PROJECTION);		   
	glLoadIdentity();					   

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glOrthof(0.0f, static_cast<float>(gameHeader.iScreenWidth), static_cast<float>(gameHeader.iScreenHeight), 0.0f, 0.0f, 1.0f);
#else
	// Set up orthographic mode
	glOrtho(0.0f, static_cast<float>(gameHeader.iScreenWidth), static_cast<float>(gameHeader.iScreenHeight), 0.0f, 0.0f, 1.0f);
#endif
	
	// Reset modelview matrix
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();					

	// Render the hardware view
	Hardware::render();

#if defined __ANDROID__ || defined MARMALADE
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
#elif defined __IOS__
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uDefaultFrameBuffer);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, gameHeader.iWindowedWidth, gameHeader.iWindowedHeight);

	// Reset project matrix
	glMatrixMode(GL_PROJECTION);		   
	glLoadIdentity();					   

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	// Set up orthographic mode
	glOrthof(0.0f, static_cast<float>(gameHeader.iWindowedWidth), static_cast<float>(gameHeader.iWindowedHeight), 0.0f, 0.0f, 1.0f);
#else
	// Set up orthographic mode
	glOrtho(0.0f, static_cast<float>(gameHeader.iWindowedWidth), static_cast<float>(gameHeader.iWindowedHeight), 0.0f, 0.0f, 1.0f);
#endif
	
	// Reset modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();					

	VertexBuffer*	pVertexBuffer	= m_vecVertexBuffers[m_iVertexBuffer];
	
	int	iVertices;

	CustomVertex*	pBuffer	= static_cast<CustomVertex*>(pVertexBuffer->getBuffer(iVertices));

	int	iStride	= sizeof(CustomVertex);

	glVertexPointer(2, GL_FLOAT, iStride, &pBuffer[0].fX);
	glTexCoordPointer(2, GL_FLOAT, iStride, &pBuffer[0].fU);

	glBindTexture(GL_TEXTURE_2D, m_uRenderTexture);

	// Draw the render buffer
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// Disable vertex and texture coordinate arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Disable texturing
	glDisable(GL_TEXTURE_2D);

	m_pGLPlatform->swapBuffers();

	return	true;
}

void Display::clear(uint32_t _uColor)
{
	GLclampf	fAlpha	= ((_uColor & 0xFF000000) >> 24) / 255.0f;
	GLclampf	fRed	= ((_uColor & 0xFF0000) >> 16) / 255.0f;
	GLclampf	fGreen	= ((_uColor & 0xFF00) >> 8) / 255.0f;
	GLclampf	fBlue	= ((_uColor & 0xFF)) / 255.0f;

	glClearColor(fRed, fGreen, fBlue, fAlpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::resize()
{
	setupTransform();
	setupVertices();
}

int Display::createVertexBuffer(int _iVertices, bool _bDynamic)
{
	VertexBuffer*	pVertexBuffer	= new VertexBuffer();

	if (false == pVertexBuffer->create(_iVertices, _bDynamic))
	{
		delete	pVertexBuffer;

		return	-1;
	}

	int	iIndex	= static_cast<int>(m_vecVertexBuffers.size());

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

	if (false == pIndexBuffer->create(_iVertices, _bDynamic))
	{
		delete	pIndexBuffer;

		return	-1;
	}

	int	iIndex	= static_cast<int>(m_vecIndexBuffers.size());

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

		if (false == pTexture->create(_iWidth, _iHeight, _eFormat, false == m_bDynamicTextures ? false : _bDynamic))
		{
			delete	pTexture;

			return	-1;
		}

		TextureData	textureData;

		textureData.pTexture		= pTexture;
		textureData.iReferenceCount	= 1;

		m_mapTextures[iHash]		=  textureData;
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
	glBindTexture(GL_TEXTURE_2D, m_mapTextures[_iHash].pTexture->getTexture());
}

bool Display::drawTriangles(int _iVertexBufferIndex, int _iVertices, int _iIndexBufferIndex, int _iTriangles)
{
	ASSERT_LOG(_iVertexBufferIndex >= 0 && _iVertexBufferIndex < static_cast<int>(m_vecVertexBuffers.size()),
		"Vertex buffer index is invalid.Debug session ended\n");
	
	ASSERT_LOG(_iIndexBufferIndex >= 0 && _iIndexBufferIndex < static_cast<int>(m_vecIndexBuffers.size()),
		"Index buffer index is invalid.\n");

	VertexBuffer*	pVertexBuffer	= m_vecVertexBuffers[_iVertexBufferIndex];
	
	int	iVertices;

	CustomVertex*	pBuffer	= reinterpret_cast<CustomVertex*>(pVertexBuffer->getBuffer(iVertices));

	int	iStride	= sizeof(CustomVertex);

	glVertexPointer(2, GL_FLOAT, iStride, &pBuffer[0].fX);
	glTexCoordPointer(2, GL_FLOAT, iStride, &pBuffer[0].fU);

	if (_iIndexBufferIndex != -1)
	{
		int	iIndices;

		GLushort*	pIndexBuffer	= reinterpret_cast<GLushort*>(m_vecIndexBuffers[_iIndexBufferIndex]->getBuffer(iIndices));

		glDrawElements(GL_TRIANGLES, _iTriangles * 3, GL_UNSIGNED_SHORT, pIndexBuffer);
	}
	
	else
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, iVertices);
	}
	
	return	true;
}

void Display::setClipRect(const Rect& _rctClip)
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	glScissor(_rctClip.iLeft, gameHeader.iScreenHeight - _rctClip.bottom(), _rctClip.iWidth, _rctClip.iHeight);

	glEnable(GL_SCISSOR_TEST);
}

void Display::resetClipRect()
{
	glDisable(GL_SCISSOR_TEST);
}

bool Display::initializeOpenGL()
{
#if !defined __ANDROID__ && !defined __IOS__ && !defined MARMALADE
	glewExperimental	= GL_TRUE;

	GLenum	error	= glewInit();
    
	if (error != GLEW_OK)
	{
		Log::instance()->logError("Unable to initialize glew %d.", error);

		return	false;
	}
#endif

	// Setup device
	if (false == setupDevice())
	{
		return	false;
	}

	const GameHeader&	gameHeader	= System::getGameHeader();

	// Create render target
	if (false == createRenderTarget(gameHeader.iScreenWidth, gameHeader.iScreenHeight))
	{
		return	false;
	}

	return	true;
}

void Display::closeOpenGL()
{	
#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_TEXTURE_2D, 0, 0);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}
#endif

	// Eat any errors
	glGetError();
}

bool Display::setupDevice()
{
	// Set culling mode
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	// Set shading
	glShadeModel(GL_FLAT);

	// Disable depth buffer
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	// Disable alpha test
	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 1.0f);

	// Disable scissor
	glDisable(GL_SCISSOR_TEST);

	// Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable lower accuracy for faster drawing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

	return	true;
}

bool Display::createRenderTarget(int _iWidth, int _iHeight, GLint _iFormat)
{
	int	iMaxRenderBufferSize;

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_OES, &iMaxRenderBufferSize);
#else
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &iMaxRenderBufferSize);
#endif

	GLenum	error	= glGetError();

	if (GL_NO_ERROR == error && (_iWidth > iMaxRenderBufferSize || _iHeight > iMaxRenderBufferSize))
	{
		return	false;
	}
		
#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glGenFramebuffersOES(1, &m_uFrameBuffer);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glGenFramebuffers(1, &m_uFrameBuffer);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glGenFramebuffersEXT(1, &m_uFrameBuffer);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create frame buffer %d", error);

		return	false;
	}

	// Create render texture
	glGenTextures(1, &m_uRenderTexture);

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create render texture %d", error);

		return	false;
	}

	glBindTexture(GL_TEXTURE_2D, m_uRenderTexture);

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to bind render texture %d", error);

		return	false;
	}

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	int	iTextureWidth	= static_cast<int>(pow(2, ceil(Utilities::log2(_iWidth))));
	int	iTextureHeight	= static_cast<int>(pow(2, ceil(Utilities::log2(_iHeight))));
#else
	int	iTextureWidth	= _iWidth;
	int	iTextureHeight	= _iHeight;
#endif
	
#if defined USE_16BIT
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iTextureWidth, iTextureHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);
#elif defined __ANDROID__ || defined MARMALADE
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iTextureWidth, iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
#elif defined __IOS__
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iTextureWidth, iTextureHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NULL);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iTextureWidth, iTextureHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
#endif

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create render texture %d", error);

		return	false;
	}

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	m_fU2	= static_cast<float>(_iWidth) / static_cast<float>(iTextureWidth);
	m_fV2	= static_cast<float>(_iHeight) / static_cast<float>(iTextureHeight);
#else
	m_fU2	= 1.0f;
	m_fV2	= 1.0f;
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uFrameBuffer);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBuffer);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER, m_uFrameBuffer);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to bind frame buffer %d", error);

		return	false;
	}

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_TEXTURE_2D, m_uRenderTexture, 0);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uRenderTexture, 0);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uRenderTexture, 0);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to attach texture to framebuffer %d", error);

		return	false;
	}

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	error	= glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES);
#else
	if (GLEW_ARB_framebuffer_object)
	{
	    error	= glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
	    error	= glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

#if defined __ANDROID__ || defined __IOS__ || defined MARMALADE
	if (error != GL_FRAMEBUFFER_COMPLETE_OES)
#else
	if (error != GL_FRAMEBUFFER_COMPLETE)
#endif
	{
		Log::instance()->logError("Unable to setup frame buffer %d", error);

		return	false;
	}

	if (false == createVertexBuffer())
	{
		Log::instance()->logError("Unable to create frame buffer vertex buffer");

		return	false;
	}

#if defined __ANDROID__ || defined MARMALADE
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
#elif defined __IOS__
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uDefaultFrameBuffer);
#else
	if (GLEW_ARB_framebuffer_object)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	else if (GLEW_EXT_framebuffer_object)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}

	else
	{
		Log::instance()->logError("Framebuffer objects not supported");

		return	false;
	}
#endif

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

	float	fOffsetX	= static_cast<float>(m_ptOffset.iX);
	float	fOffsetY	= static_cast<float>(m_ptOffset.iY);

	// (0)*--*(2)
	//    | /|
	// (1)*--*(3)
	// UVs are flipped to adjust for OpenGL's coordinate system
	int	iIndex	= 0;

#ifdef __IOS__
	const GameHeader&	gameHeader	= System::getGameHeader();

	float	fScreenWidth	= static_cast<float>(gameHeader.iWindowedWidth);
	float	fScreenHeight	= static_cast<float>(gameHeader.iWindowedHeight);

	if (true == gameHeader.bPortrait)
	{
		pBuffer[iIndex].fX	= (320 - gameHeader.iScreenWidth) / 2;
		pBuffer[iIndex].fY	= 8 + (256 - gameHeader.iScreenHeight) / 2;
	}

	else
	{
		pBuffer[iIndex].fX	= fOffsetX;
		pBuffer[iIndex].fY	= fOffsetY;
	}
#else
	pBuffer[iIndex].fX	= fOffsetX;
	pBuffer[iIndex].fY	= fOffsetY;
#endif

	pBuffer[iIndex].fU	= 0.0;
	pBuffer[iIndex].fV	= m_fV2;
	
	iIndex++;

#ifdef __IOS__
	if (true == gameHeader.bPortrait)
	{
		pBuffer[iIndex].fX	= (320 - gameHeader.iScreenWidth) / 2;
		pBuffer[iIndex].fY	= 8 + 256 - (256 - gameHeader.iScreenHeight) / 2;
	}

	else
	{
		pBuffer[iIndex].fX	= fOffsetX;
		pBuffer[iIndex].fY	= fScreenHeight - fOffsetY;
	}
#else
	pBuffer[iIndex].fX	= fOffsetX;
	pBuffer[iIndex].fY	= fOffsetY + m_fRenderHeight;
#endif

	pBuffer[iIndex].fU	= 0.0f;
	pBuffer[iIndex].fV	= 0.0f;
	
	iIndex++;

#ifdef __IOS__
	if (true == gameHeader.bPortrait)
	{
		pBuffer[iIndex].fX	= 320 - (320 - gameHeader.iScreenWidth) / 2;
		pBuffer[iIndex].fY	= 8 + (256 - gameHeader.iScreenHeight) / 2;
	}

	else
	{
		pBuffer[iIndex].fX	= fScreenWidth - fOffsetX;
		pBuffer[iIndex].fY	= fOffsetY;
	}
#else
	pBuffer[iIndex].fX	= fOffsetX + m_fRenderWidth;
	pBuffer[iIndex].fY	= fOffsetY;
#endif

	pBuffer[iIndex].fU	= m_fU2;
	pBuffer[iIndex].fV	= m_fV2;
	
	iIndex++;

#ifdef __IOS__
	if (true == gameHeader.bPortrait)
	{
		pBuffer[iIndex].fX	= 320 - (320 - gameHeader.iScreenWidth) / 2;
		pBuffer[iIndex].fY	= 8 + 256 - (256 - gameHeader.iScreenHeight) / 2;
	}

	else
	{
		pBuffer[iIndex].fX	= fScreenWidth - fOffsetX;
		pBuffer[iIndex].fY	= fScreenHeight - fOffsetY;
	}
#else
	pBuffer[iIndex].fX	= fOffsetX + m_fRenderWidth;
	pBuffer[iIndex].fY	= fOffsetY + m_fRenderHeight;
#endif

	pBuffer[iIndex].fU	= m_fU2;
	pBuffer[iIndex].fV	= 0.0f;

	pVertexBuffer->releaseBuffer();

	return	true;
}

void Display::setupTransform()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
#ifdef __IOS__
	int iWindowedWidth	= gameHeader.iWindowedHeight;
	int iWindowedHeight	= gameHeader.iWindowedWidth;

	if (true == gameHeader.bPortrait)
	{
		iWindowedWidth	= 320;
		iWindowedHeight	= 240;
	}
#else
	int iWindowedWidth	= gameHeader.iWindowedWidth;
	int iWindowedHeight	= gameHeader.iWindowedHeight;
#endif

	float	fScreenWidth	= static_cast<float>(gameHeader.iScreenWidth);
	float	fScreenHeight	= static_cast<float>(gameHeader.iScreenHeight);
	float	fScaleX			= static_cast<float>(iWindowedWidth) / fScreenWidth;
	float	fScaleY			= static_cast<float>(iWindowedHeight) / fScreenHeight;

	m_ptOffset.iX	= 0;
	m_ptOffset.iY	= 0;

	float	fScale;

	if (fScaleX >= fScaleY)
	{
		m_ptOffset.iX	= ((iWindowedWidth - static_cast<int>(fScreenWidth * fScaleY)) / 2);

		fScale	= fScaleY;
	}
	
	else
	{
		m_ptOffset.iY	= ((iWindowedHeight - static_cast<int>(fScreenHeight * fScaleX)) / 2);

		fScale	= fScaleX;
	}

	m_fRenderWidth	= fScreenWidth * fScale;
	m_fRenderHeight	= fScreenHeight * fScale;
}

ENDNAMESPACE
