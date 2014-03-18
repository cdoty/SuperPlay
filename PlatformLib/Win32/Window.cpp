// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <windowsx.h>

#include "GameHeader.h"
#include "IDisplay.h"
#include "Input.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"
#include "Resources/resource.h"

NAMESPACE(SPlay)

// Window class name
static const char*	gsc_szClassName	= "SPlayWindow";

Window::Window()	:
	m_hWnd(NULL)
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
	
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	bool	bFullscreen	= gameHeader.bFullScreen;

	DWORD	dwStyle	= true == bFullscreen ? (WS_EX_TOPMOST | WS_POPUP) : WS_OVERLAPPEDWINDOW;

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
		m_iWidth	= gameHeader.iWindowedWidth;
		m_iHeight	= gameHeader.iWindowedHeight;
	}

	// Create window
	m_hWnd	= CreateWindow(gsc_szClassName, gameHeader.strAppName.c_str(), dwStyle, true == bFullscreen ? 0 : CW_USEDEFAULT, 
		true == bFullscreen ? 0 : CW_USEDEFAULT, m_iWidth, m_iHeight, NULL, NULL, m_hInstance, "");
	
	if (NULL == m_hWnd)
	{
		Log::instance()->logError("Unable to create window (%08X)", GetLastError());
		
		return	false;
	}

	if (false == bFullscreen)
	{
		resizeClientArea();
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
	showMouse(true);

	if (m_hInstance != NULL)
	{
		UnregisterClass(gsc_szClassName, m_hInstance);
		
		m_hInstance	= NULL;
	}
}

LRESULT CALLBACK Window::messageProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT	_sPaintStruct;

	switch (_msg)
	{
		case WM_SIZE:
		{
			GameHeader&	gameHeader	= System::getUpdateableGameHeader();

			gameHeader.iWindowedWidth	= LOWORD(_lParam);
			gameHeader.iWindowedHeight	= HIWORD(_lParam);

			System::getDisplay()->resize();

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

ENDNAMESPACE
