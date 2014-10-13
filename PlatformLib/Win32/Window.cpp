// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <windows.h>

#include "GameHeader.h"
#include "IDisplay.h"
#include "Input.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "ResourceManager.h"
#include "System.h"
#include "Window.h"
#include "Resources/resource.h"

NAMESPACE(SPlay)

// Window class name
static const char*	gsc_szClassName	= "SPlayWindow";

Window::Window()	:
	m_hWnd(NULL),
	m_hLayeredBitmap(NULL),
	m_hLayeredDC(NULL),
	m_pLayeredBuffer(NULL),
	m_pRenderBuffer(NULL),
	m_pFrameBuffer(NULL)
{
}

Window::~Window()
{
	close();
}

Window* Window::create()
{
	Window*	pWindow	= new Window();
	
	if (false == pWindow->initialize())
	{
		delete	pWindow;
		
		pWindow	= NULL;
	}	
	
	return	pWindow;
}

bool Window::initialize()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	bool	bFramed	= true == gameHeader.bFramedWindow && false == gameHeader.bFullScreen;

	if (true == bFramed && false == loadFrame())
	{
		return	false;
	}

	WNDCLASS	sWndClass;	
	
	m_hInstance	= GetModuleHandle(NULL);
	
	sWndClass.style			= CS_HREDRAW | CS_VREDRAW;
	sWndClass.lpfnWndProc	= messageProc;
	sWndClass.cbClsExtra	= 0;
	sWndClass.cbWndExtra	= 0;
	sWndClass.hInstance		= m_hInstance;
	sWndClass.hIcon			= LoadIcon(m_hInstance, MAKEINTRESOURCE(ICON_PROGRAM));
	sWndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	sWndClass.hbrBackground	= NULL;
	sWndClass.lpszMenuName	= NULL;
	sWndClass.lpszClassName	= gsc_szClassName;

	// Register windows class
	m_sClassAtom	= RegisterClass(&sWndClass);

	if (0 == m_sClassAtom)
	{
		Log::instance()->logError("Unable to register windows class (%08X)", GetLastError());
		
		return	false;
	}
	
	bool	bFullscreen	= gameHeader.bFullScreen;

	DWORD	dwStyle	= true == bFullscreen ? (WS_EX_TOPMOST | WS_POPUP) : WS_OVERLAPPEDWINDOW;

	DWORD	dwExStyle	= 0;

	if (true == bFramed)
	{
		// Layered window
		dwExStyle	|= WS_EX_LAYERED;
		dwStyle		= WS_POPUP;
	}

	if (true == bFullscreen)
	{
		HDC	hDC	= GetDC(NULL);

		if (NULL == hDC)
		{
			Log::instance()->logError("Unable to get desktop DC (%08X)", GetLastError());
		
			return	true;
		}
		
		m_iWidth	= GetDeviceCaps(hDC, HORZRES);
		m_iHeight	= GetDeviceCaps(hDC, VERTRES);

		ReleaseDC(NULL, hDC);
	}

	else
	{
		if (true == bFramed)
		{
			m_iWidth	= m_iFrameWidth;
			m_iHeight	= m_iFrameHeight;
		}

		else
		{
			m_iWidth	= gameHeader.iWindowedWidth;
			m_iHeight	= gameHeader.iWindowedHeight;
		}
	}

	// Create window
	m_hWnd	= CreateWindowEx(dwExStyle, gsc_szClassName, gameHeader.strAppName.c_str(), dwStyle, true == bFullscreen ? 0 : CW_USEDEFAULT, 
		true == bFullscreen ? 0 : CW_USEDEFAULT, m_iWidth, m_iHeight, NULL, NULL, m_hInstance, "");
	
	if (NULL == m_hWnd)
	{
		Log::instance()->logError("Unable to create window (%08X)", GetLastError());
		
		return	false;
	}

	if (false == bFullscreen)
	{
		if (true == bFramed)
		{
			if (false == createLayeredWindow())
			{
				return	false;
			}

			centerWindow();
		}

		else
		{
			resizeClientArea();
		}
	}
	
	else
	{
		showMouse(false);
	}

	// Show and activate window
	ShowWindow(m_hWnd, SW_SHOW);
	SetActiveWindow(m_hWnd);
	SetFocus(m_hWnd);

	return	true;
}

void Window::close()
{
	destroyLayeredWindow();

	showMouse(true);

	if (m_hInstance != NULL)
	{
		UnregisterClass(gsc_szClassName, m_hInstance);
		
		m_hInstance	= NULL;
	}
}

void Window::drawLayeredWindow()
{
	drawScreen();

	updateLayeredWindow();
}

LRESULT CALLBACK Window::messageProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT	_sPaintStruct;

	switch (_msg)
	{
		case WM_SIZE:
		{
			GameHeader&	gameHeader	= System::getUpdateableGameHeader();

			if (false == gameHeader.bFramedWindow || true == gameHeader.bFullScreen)
			{
				gameHeader.iWindowedWidth	= LOWORD(_lParam);
				gameHeader.iWindowedHeight	= HIWORD(_lParam);

				System::getDisplay()->resize();
			}

			break;
		}

		case WM_KEYDOWN:
			return	TRUE;
			
		case WM_KEYUP:
			return	TRUE;
			
		case WM_LBUTTONDOWN:
			return	TRUE;

		case WM_LBUTTONUP:
			return	TRUE;

		case WM_CLOSE:
			DestroyWindow(_hWnd);

			return	0;

		case WM_NCHITTEST:
		{			
			const GameHeader&	gameHeader	= System::getGameHeader();

			if (true == gameHeader.bFramedWindow && false == gameHeader.bFullScreen)
			{
				return	HTCAPTION;
			}

			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);

			break;
	
		case WM_PAINT:
			BeginPaint(_hWnd, &_sPaintStruct);
			EndPaint(_hWnd, &_sPaintStruct);

			return	FALSE;

		case WM_DEVICECHANGE:
			if (System::getInput() != NULL)
			{
				System::getInput()->deviceChange();
			}

			break;

		case WM_ERASEBKGND:
			return	TRUE;
	
#if 0
		case WM_SETFOCUS:
			SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

			break;

		case WM_KILLFOCUS:
			SetWindowPos(_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

			break;
#endif
	}

	return	DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

void Window::resizeClientArea()
{
	RECT	rctClient;
	RECT	rctWindow;

	// Calculate the amount to extend the window so that the client area is the requested width and height
	GetClientRect(m_hWnd, &rctClient);
	GetWindowRect(m_hWnd, &rctWindow);
	
	int	iDiffX	= (rctWindow.right - rctWindow.left) - rctClient.right;
	int	iDiffY	= (rctWindow.bottom - rctWindow.top) - rctClient.bottom;
	
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	MoveWindow(m_hWnd, rctWindow.left, rctWindow.top, gameHeader.iWindowedWidth + iDiffX, gameHeader.iWindowedHeight + iDiffY, TRUE);
}

void Window::centerWindow()
{
	RECT	rctWindow;

	GetWindowRect(m_hWnd, &rctWindow);

	MONITORINFO	monitorInfo	= {0};

	monitorInfo.cbSize	= sizeof(monitorInfo);

	GetMonitorInfo(MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST), &monitorInfo);

	RECT rctMonitor	= monitorInfo.rcWork;

	int	iWindowWidth	= rctWindow.right - rctWindow.left;
	int	iWindowHeight	= rctWindow.bottom - rctWindow.top;

	int	iLeft	= (rctMonitor.left + rctMonitor.right) / 2 - iWindowWidth / 2;
	int	iTop	= (rctMonitor.top + rctMonitor.bottom) / 2 - iWindowHeight / 2;

	if (iLeft < rctMonitor.left)
	{
		iLeft	= rctMonitor.left;
	}

	else if (iLeft + iWindowWidth > rctMonitor.right)
	{
		iLeft	= rctMonitor.right - iWindowWidth;
	}

	if (iTop < rctMonitor.top)
	{
		iTop	= rctMonitor.top;
	}

	else if (iTop + iWindowHeight > rctMonitor.bottom)
	{
		iTop	= rctMonitor.bottom - iWindowHeight;
	}

	SetWindowPos(m_hWnd, NULL, iLeft, iTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void Window::showMouse(bool _bShow)
{
	if (true == _bShow)
	{
		while (ShowCursor(TRUE) < 0)
		{
		}
	}
	
	else
	{
		while (ShowCursor(FALSE) >= 0)
		{
		}
	}
}

bool Window::loadFrame()
{
	ResourceManager*	pResourceManager	= System::getResourceManager();

	int	iImage	= pResourceManager->loadImage("frame.png");

	if (-1 == iImage)
	{
		Log::instance()->logError("Unable to load frame image");

		return	false;
	}

	Image*	pImage	= pResourceManager->getImage(iImage);
	
	m_iFrameWidth	= pImage->getWidth();
	m_iFrameHeight	= pImage->getHeight();
	
	int	iSize	= m_iFrameWidth * m_iFrameHeight * 4;

	m_pFrameBuffer	= new uint8_t[iSize];

	memcpy(m_pFrameBuffer, pImage->getPixels(), iSize);
	
	premultiplyAlpha(m_pFrameBuffer, m_iFrameWidth, m_iFrameHeight);

	int	iStartX;
	int	iStartY;

	getFramePoint(iStartX, iStartY);

	if (-1 == iStartX || -1 == iStartY)
	{
		Log::instance()->logError("Unable to find frame offset");
		
		return	false;
	}

	m_iFrameOffset	= (iStartY * m_iFrameWidth + iStartX) * 4;

	return	true;
}

void Window::getFramePoint(int& _iX, int& _iY)
{
	_iX	= -1;
	_iY	= -1;

	uint8_t*	pBuffer	= m_pFrameBuffer;

	for (int iYLoop = 0; iYLoop < m_iFrameHeight; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < m_iFrameWidth; ++iXLoop)
		{
			if (pBuffer[0] == 0xFF && pBuffer[1] == 0x00 && pBuffer[2] == 0xFF && pBuffer[3] == 0xFF)
			{
				_iX	= iXLoop;
				_iY	= iYLoop;

				return;
			}
			
			pBuffer	+= 4;
		}
	}
}

bool Window::createLayeredWindow()
{
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	m_iLayeredWidth		= gameHeader.iWindowedWidth;
	m_iLayeredHeight	= gameHeader.iWindowedHeight;

	m_pLayeredBuffer	= new uint8_t[m_iLayeredWidth * m_iLayeredHeight * 4];

	m_hLayeredDC		= CreateCompatibleDC(NULL);

	if (NULL == m_hLayeredDC)
	{
		Log::instance()->logError("Unable to create layered DC (%08X)", GetLastError());
		
		return	false;
	}

	memset(&m_layeredBitmapInfo, 0, sizeof(m_layeredBitmapInfo));

	m_layeredBitmapInfo.bmiHeader.biSize		= sizeof(m_layeredBitmapInfo.bmiHeader);
	m_layeredBitmapInfo.bmiHeader.biBitCount	= 32;
	m_layeredBitmapInfo.bmiHeader.biWidth		= m_iFrameWidth;
	m_layeredBitmapInfo.bmiHeader.biHeight		= -m_iFrameHeight;
	m_layeredBitmapInfo.bmiHeader.biCompression	= BI_RGB;
	m_layeredBitmapInfo.bmiHeader.biPlanes		= 1;

	m_hLayeredBitmap	= CreateDIBSection(m_hLayeredDC, &m_layeredBitmapInfo, DIB_RGB_COLORS, (void**)&m_pRenderBuffer, NULL, 0);

	if (NULL == m_hLayeredBitmap)
	{
		Log::instance()->logError("Unable to create layered bitmap (%08X)", GetLastError());
		
		return	false;
	}

	GdiFlush();

	memcpy(m_pRenderBuffer, m_pFrameBuffer, m_iFrameWidth * m_iFrameHeight * 4);

	return	true;	
}

void Window::destroyLayeredWindow()
{
	delete[]	m_pFrameBuffer;
	delete[]	m_pLayeredBuffer;

	m_pFrameBuffer	= NULL;

	if (m_hLayeredBitmap != NULL)
	{
		DeleteObject(m_hLayeredBitmap);

		m_hLayeredBitmap	= NULL;
	}

	if (m_hLayeredDC != NULL)
	{
		DeleteDC(m_hLayeredDC);

		m_hLayeredDC	= NULL;
	}
}

void Window::premultiplyAlpha(uint8_t* _pBuffer, int _iWidth, int _iHeight)
{
	int	t_c	= _iWidth * _iHeight;

	uint8_t*	pBuffer	= _pBuffer;

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		uint8_t	pAlpha	= (uint8_t)((float)pBuffer[3] / 255.0f);

		pBuffer[0]	*= pAlpha;
		pBuffer[1]	*= pAlpha;
		pBuffer[2]	*= pAlpha;

		pBuffer	+= 4;
	}
}

void Window::drawScreen()
{
	uint8_t*	pSrc	= m_pLayeredBuffer;
	uint8_t*	pDest	= m_pRenderBuffer + m_iFrameOffset;

	int	iStride	= (m_iFrameWidth - m_iLayeredWidth) * 4;

	for (int iYLoop = 0; iYLoop < m_iLayeredHeight; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < m_iLayeredWidth; ++iXLoop)
		{
			uint8_t	pAlpha	= (uint8_t)((float)pSrc[3] / 255.0f);

			pDest[0]	= pSrc[0] * pAlpha;
			pDest[1]	= pSrc[1] * pAlpha;
			pDest[2]	= pSrc[2] * pAlpha;

			pSrc	+= 4;
			pDest	+= 4;
		}

		pDest	+= iStride;
	}
}

void Window::updateLayeredWindow()
{
	HDC	hDC	= GetDC(m_hWnd);

	if (hDC != NULL)
	{
		SIZE	szWindow	= {m_iFrameWidth, m_iFrameHeight};

		BLENDFUNCTION	blendFunction	= {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};

		HGDIOBJ	hPrevious	= SelectObject(m_hLayeredDC, m_hLayeredBitmap);

		POINT	ptSrc	= {0, 0};
		POINT	ptDest	= {0, 0};

		ClientToScreen(m_hWnd, &ptDest);

		if (FALSE == UpdateLayeredWindow(m_hWnd, hDC, &ptDest, &szWindow, m_hLayeredDC, &ptSrc, 0, &blendFunction, ULW_ALPHA))
		{
			Log::instance()->logError("Unable to update layered window (%08X)", GetLastError());
		}
		
		SelectObject(m_hLayeredDC, hPrevious);
		ReleaseDC(m_hWnd, hDC);
	}
}

ENDNAMESPACE
