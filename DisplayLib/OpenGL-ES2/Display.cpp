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

#include "PixelShader.h"
#include "VertexShader.h"

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

	if (false == compileShaders())
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
		glDeleteFramebuffers(1, &m_uFrameBuffer);
		
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

	glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBuffer);

	// Use shader program
	glUseProgram(m_uShaderProgram);

	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, gameHeader.iScreenWidth, gameHeader.iScreenHeight);

	loadMatrix("matMatrix", m_matSimulatedTransform);

	// Render the hardware view
	Hardware::render();

#if defined __IOS__
	glBindFramebuffer(GL_FRAMEBUFFER, m_uDefaultFrameBuffer);
#else
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, gameHeader.iWindowedWidth, gameHeader.iWindowedHeight);

	loadMatrix("matMatrix", m_matRenderTransform);
	
	glEnableVertexAttribArray(m_iVertexArray);

	glEnableVertexAttribArray(m_iUVArray);
   
	VertexBuffer*	pVertexBuffer	= m_vecVertexBuffers[m_iVertexBuffer];
	
	int	iVertices;

	CustomVertex*	pBuffer	= static_cast<CustomVertex*>(pVertexBuffer->getBuffer(iVertices));

	int	iStride	= sizeof(CustomVertex);

	glVertexAttribPointer(m_iVertexArray, 2, GL_FLOAT, GL_FALSE, iStride, &pBuffer[0].fX);

	glVertexAttribPointer(m_iUVArray, 2, GL_FLOAT, GL_FALSE, iStride, &pBuffer[0].fU);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uRenderTexture);

	glUniform1i(m_iTexture, 0);

	// Draw the render buffer
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// Disable vertex and texture coordinate arrays
	glDisableVertexAttribArray(m_iVertexArray);	
	glDisableVertexAttribArray(m_iUVArray);	

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
	ASSERT_LOG(_iIndex >= 0 && _iIndex < static_cast<int>(m_vecVertexBuffers.size()), "Vertex buffer index is invalid.");

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
	ASSERT_LOG(_iIndex >= 0 && _iIndex < static_cast<int>(m_vecVertexBuffers.size()), "Vertex buffer index is invalid.");

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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_mapTextures[_iHash].pTexture->getTexture());

	glUniform1i(m_iTexture, 0);
}

bool Display::drawTriangles(int _iVertexBufferIndex, int _iVertices, int _iIndexBufferIndex, int _iTriangles)
{
	ASSERT_LOG(_iVertexBufferIndex >= 0 && _iVertexBufferIndex < static_cast<int>(m_vecVertexBuffers.size()),
		"Vertex buffer index is invalid.Debug session ended");
	
	ASSERT_LOG(_iIndexBufferIndex >= 0 && _iIndexBufferIndex < static_cast<int>(m_vecIndexBuffers.size()),
		"Index buffer index is invalid.");

	VertexBuffer*	pVertexBuffer	= m_vecVertexBuffers[_iVertexBufferIndex];
	
	int	iVertices;

	glEnableVertexAttribArray(m_iVertexArray);
	glEnableVertexAttribArray(m_iUVArray);
   
	CustomVertex*	pBuffer	= reinterpret_cast<CustomVertex*>(pVertexBuffer->getBuffer(iVertices));

	int	iStride	= sizeof(CustomVertex);

	glVertexAttribPointer(m_iVertexArray, 2, GL_FLOAT, false, iStride, &pBuffer[0].fX);
	glVertexAttribPointer(m_iUVArray, 2, GL_FLOAT, false, iStride, &pBuffer[0].fU);

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
	
	// Disable vertex and texture coordinate arrays
	glDisableVertexAttribArray(m_iVertexArray);	
	glDisableVertexAttribArray(m_iUVArray);	

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
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Eat any errors
	glGetError();
}

bool Display::setupDevice()
{
	// Set culling mode
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	// Disable depth buffer
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	// Disable scissor
	glDisable(GL_SCISSOR_TEST);

	// Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	return	true;
}

bool Display::createRenderTarget(int _iWidth, int _iHeight, GLint _iFormat)
{
	glGenFramebuffers(1, &m_uFrameBuffer);

	GLenum	error	= glGetError();

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

	int	iTextureWidth	= static_cast<int>(pow(2, ceil(Utilities::log2(_iWidth))));
	int	iTextureHeight	= static_cast<int>(pow(2, ceil(Utilities::log2(_iHeight))));
	
#if defined __IOS__
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iTextureWidth, iTextureHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NULL);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iTextureWidth, iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
#endif

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to create render texture %d", error);

		return	false;
	}

	m_fU2	= static_cast<float>(_iWidth) / static_cast<float>(iTextureWidth);
	m_fV2	= static_cast<float>(_iHeight) / static_cast<float>(iTextureHeight);

	// Set render texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBuffer);

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to bind frame buffer %d", error);

		return	false;
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uRenderTexture, 0);

	error	= glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::instance()->logError("Unable to attach texture to framebuffer %d", error);

		return	false;
	}

	error	= glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (error != GL_FRAMEBUFFER_COMPLETE)
	{
		Log::instance()->logError("Unable to setup frame buffer %d", error);

		return	false;
	}

	if (false == createVertexBuffer())
	{
		Log::instance()->logError("Unable to create frame buffer vertex buffer");

		return	false;
	}

#if defined __IOS__
	glBindFramebuffer(GL_FRAMEBUFFER, m_uDefaultFrameBuffer);
#elif defined __ANDROID__ || defined MARMALADE || defined EMSCRIPTEN || defined ANGLE
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

	// Create simulated transform
	Matrix4f	matProjection	= Matrix4f::createOrtho(0.0f, static_cast<float>(gameHeader.iScreenWidth), static_cast<float>(gameHeader.iScreenHeight), 0.0f, 0.0f, 1.0f);
	Matrix4f	matScale		= Matrix4f::createScale(1.0f, 1.0f, 1.0f);
	Matrix4f	matTranslate	= Matrix4f::createTranslation(static_cast<float>(0.0f), static_cast<float>(0.0f), 0.0f);
	
	m_matSimulatedTransform	= matProjection * matScale * matTranslate;

	// Create render transform
	matProjection	= Matrix4f::createOrtho(0.0f, static_cast<float>(gameHeader.iWindowedWidth), static_cast<float>(gameHeader.iWindowedHeight), 0.0f, 0.0f, 1.0f);
	matScale		= Matrix4f::createScale(1.0f, 1.0f, 1.0f);
	matTranslate	= Matrix4f::createTranslation(static_cast<float>(m_ptOffset.iX), static_cast<float>(m_ptOffset.iY), 0.0f);
	
	m_matRenderTransform	= matProjection * matScale * matTranslate;
}

bool Display::compileShaders()
{
	m_uPixelShader	= glCreateShader(GL_FRAGMENT_SHADER);

	if (0 == m_uPixelShader)
	{
		Log::instance()->logError("Unable to create pixel shader %d", glGetError());

		return	false;
	}

	const GLchar*	pShader	= gsc_szPixelShader;	

	glShaderSource(m_uPixelShader, 1, &pShader, NULL);
	 
	glCompileShader(m_uPixelShader);
	
	GLint	bCompiled;

	glGetShaderiv(m_uPixelShader, GL_COMPILE_STATUS, &bCompiled);

	if (false == bCompiled)
	{
		logShaderError(m_uPixelShader, "Pixel Shader");

		return	false;
	}

	m_uVertexShader	= glCreateShader(GL_VERTEX_SHADER);

	if (0 == m_uVertexShader)
	{
		Log::instance()->logError("Unable to create vertex shader %d", glGetError());

		return	false;
	}

	pShader	= gsc_szVertexShader;

	glShaderSource(m_uVertexShader, 1, &pShader, NULL);
	 
	glCompileShader(m_uVertexShader);
	
	glGetShaderiv(m_uVertexShader, GL_COMPILE_STATUS, &bCompiled);

	if (false == bCompiled)
	{
		logShaderError(m_uVertexShader, "Vertex Shader");

		return	false;
	}

	m_uShaderProgram	= glCreateProgram();

	if (0 == m_uShaderProgram)
	{
		Log::instance()->logError("Unable to create program %d", glGetError());

		return	false;
	}

	glAttachShader(m_uShaderProgram, m_uVertexShader);
	glAttachShader(m_uShaderProgram, m_uPixelShader);
	glLinkProgram(m_uShaderProgram);

	GLint	bLinked;

	glGetProgramiv(m_uShaderProgram, GL_LINK_STATUS, &bLinked);
	
	if (false == bLinked)
	{
		logProgramError(m_uShaderProgram);

		return	false;
	}

	m_iVertexArray	= glGetAttribLocation(m_uShaderProgram, "vecVertex");
	
	if (-1 == m_iVertexArray)
	{
		Log::instance()->logError("Unable find vertex shader attribute");

		return	false;
	}
	
	m_iUVArray	= glGetAttribLocation(m_uShaderProgram, "vecUV");
	
	if (-1 == m_iUVArray)
	{
		Log::instance()->logError("Unable find texture UV shader attribute");

		return	false;
	}
	
	m_iTexture	= glGetUniformLocation(m_uShaderProgram, "pTexture");

	if (-1 == m_iTexture)
	{
		Log::instance()->logError("Unable find texture shader attribute");

		return	false;
	}

	return	true;
}

void Display::loadMatrix(const char* _szMatrixName, const Matrix4f& _matMatrix) const
{
	// Load matrix
	int iMatrix	= glGetUniformLocation(m_uShaderProgram, _szMatrixName);

	ASSERT_LOG(iMatrix != -1, "Unable to find matrix %s", _szMatrixName);

	glUniformMatrix4fv(iMatrix, 1, GL_FALSE, _matMatrix.data);
}

void Display::logShaderError(GLuint _uShaderID, const char* _szName) const
{
	int	iInfoLogLength;
	int	iActualSize;

	glGetShaderiv(_uShaderID, GL_INFO_LOG_LENGTH, &iInfoLogLength);

	char*	szInfoLog	= new char[iInfoLogLength];

	glGetShaderInfoLog(_uShaderID, iInfoLogLength, &iActualSize, szInfoLog);

	Log::instance()->logError("Shader error in %s: %s", _szName, szInfoLog);

	delete []	szInfoLog;
}

void Display::logProgramError(GLuint _uProgramID) const
{
	int	iInfoLogLength;
	int	iActualSize;

	glGetProgramiv(_uProgramID, GL_INFO_LOG_LENGTH, &iInfoLogLength);

	char*	szInfoLog	= new char[iInfoLogLength];

	glGetProgramInfoLog(_uProgramID, iInfoLogLength, &iActualSize, szInfoLog);

	Log::instance()->logError("Program error: %s", szInfoLog);

	delete []	szInfoLog;
}

ENDNAMESPACE
