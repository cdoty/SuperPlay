// Window - Class representing the window
//
// © 2011 Raster Software. All rights reserved.

#include <windowsx.h>

#include "Log.h"
#include "Window.h"
#include "..\resource.h"

// Window class name
static const char*	gsc_szClassName	= "SPPopup";

// Default app name
static const char*	gsc_szAppName	= "Joypad Test";

// Point size
static const int	gsc_iPointSize	= 8;

Window::Window()	:
	m_hWnd(NULL),
	m_iInput(-1)
{
}

Window::~Window()
{
	close();
}

WindowPtr Window::create()
{
	WindowPtr	pWindow(new Window());
	
	if (false == pWindow->initialize())
	{
		pWindow.reset();
	}	
	
	return	pWindow;
}

bool Window::initialize()
{
	m_pSkin	= Skin::create();

	if (nullptr == m_pSkin)
	{
		return	false;
	}

	int	iWidth	= m_pSkin->getWidth();
	int	iHeight	= m_pSkin->getHeight();
	
	WNDCLASS	sWndClass;	
	
	m_hInstance	= GetModuleHandle(NULL);
	
	sWndClass.style			= CS_OWNDC;
	sWndClass.lpfnWndProc	= messageProc;
	sWndClass.cbClsExtra	= 0;
	sWndClass.cbWndExtra	= 0;
	sWndClass.hInstance		= m_hInstance;
	sWndClass.hIcon			= LoadIcon(m_hInstance, MAKEINTRESOURCE(ICON_PROGRAM));
	sWndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	sWndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	sWndClass.lpszMenuName	= NULL;
	sWndClass.lpszClassName	= gsc_szClassName;

	// Register windows class
	m_sClassAtom	= RegisterClass(&sWndClass);

	if (0 == m_sClassAtom)
	{
		Log::instance()->logError("Unable to register windows class (%08X)", GetLastError());
		
		return	false;
	}
	
	// Center the window on the screen
	int	iScreenWidth	= GetSystemMetrics(SM_CXSCREEN);
	int	iScreenHeight	= GetSystemMetrics(SM_CYSCREEN);

	// Create window
	m_hWnd	= CreateWindowEx(WS_EX_TOPMOST, gsc_szClassName, gsc_szAppName, WS_POPUP, (iScreenWidth - iWidth) / 2, 
		(iScreenHeight - iHeight) / 2, iWidth, iHeight, NULL, NULL, m_hInstance, NULL);
	
	if (NULL == m_hWnd)
	{
		Log::instance()->logError("Unable to create window (%08X)", GetLastError());
		
		return	false;
	}

	setButtonPositions();

	m_pSkin->setHWND(m_hWnd);

	if (false == m_pSkin->applyRegion())
	{
		return	false;
	}

	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);

	return	true;
}

void Window::close()
{
	if (m_hInstance != NULL)
	{
		UnregisterClass(gsc_szClassName, m_hInstance);
		
		m_hInstance	= NULL;
	}
}

void Window::run()
{
	// Show and activate window
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetActiveWindow(m_hWnd);
	SetFocus(m_hWnd);

	MSG	msg;

	memset(&msg, 0, sizeof(MSG));

	int	iSleepTime	= 0;
	
	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	ShowWindow(m_hWnd, SW_HIDE);
}

void Window::setInput(int _iInput)
{
	m_iInput = _iInput;

	InvalidateRect(m_hWnd, NULL, FALSE);
}

LRESULT CALLBACK Window::messageProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
		case WM_KEYDOWN:
			switch (_wParam)
			{
				case VK_ESCAPE:
					PostMessage(_hWnd, WM_CLOSE, 0, 0);

					return	TRUE;
			}

			break;
			
		case WM_LBUTTONDOWN:
			if (GET_X_LPARAM(_lParam) >= 256 - 12 && GET_Y_LPARAM(_lParam) < 13)
			{
				PostMessage(_hWnd, WM_CLOSE, 0, 0);
			}
			
			else
			{
				SendMessage(_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL);
			}
			
			break;

		case WM_CLOSE:
			DestroyWindow(_hWnd);

			return	0;

		case WM_DESTROY:
			PostQuitMessage(0);

			break;
	
		case WM_PAINT:
		{
			PAINTSTRUCT	_sPaintStruct;															  

			HDC	hDC	= BeginPaint(_hWnd, &_sPaintStruct);

			Window*	pWindow	= reinterpret_cast<Window*>(GetWindowLong(_hWnd, GWL_USERDATA));

			pWindow->getSkin()->redraw(hDC);

			int	iInput	= pWindow->getInput();

			if (iInput != -1)
			{
				HPEN	pen		= CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				HBRUSH	brush	= CreateSolidBrush(RGB(255, 0, 0));

				HPEN	oldPen		= static_cast<HPEN>(SelectObject(hDC, pen));
				HBRUSH	oldBrush	= static_cast<HBRUSH>(SelectObject(hDC, brush));

				POINT	position	= pWindow->getButtonPosition(iInput);

				Ellipse(hDC, position.x, position.y, position.x + gsc_iPointSize, position.y + gsc_iPointSize);
			
				SelectObject(hDC, oldBrush);
				SelectObject(hDC, oldPen);

				DeleteObject(brush);
				DeleteObject(pen);
			}

			EndPaint(_hWnd, &_sPaintStruct);

			return	TRUE;
		}

		case WM_ERASEBKGND:
			return	TRUE;
	}

	return	DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}

void Window::setButtonPositions()
{
	int	iSize	= gsc_iPointSize / 2;

	// Set dpad positions
	POINT	point1	= {54 - iSize, 43 - iSize};
	m_vecButtonPositions.push_back(point1);

	POINT	point2	= {54 - iSize, 72 - iSize};
	m_vecButtonPositions.push_back(point2);

	POINT	point3	= {40 - iSize, 57 - iSize};
	m_vecButtonPositions.push_back(point3);

	POINT	point4	= {69 - iSize, 57 - iSize};
	m_vecButtonPositions.push_back(point4);
	
	// Set ABXY positions
	POINT	point5	= {225 - iSize, 57 - iSize};
	m_vecButtonPositions.push_back(point5);

	POINT	point6	= {202 - iSize, 76 - iSize};
	m_vecButtonPositions.push_back(point6);

	POINT	point7	= {205 - iSize, 35 - iSize};
	m_vecButtonPositions.push_back(point7);

	POINT	point8	= {181 - iSize, 54 - iSize};
	m_vecButtonPositions.push_back(point8);
	
	// Set LR positions
	POINT	point9	= {59 - iSize, 3 - iSize};
	m_vecButtonPositions.push_back(point9);

	POINT	point10	= {198 - iSize, 3 - iSize};
	m_vecButtonPositions.push_back(point10);

	// Set Start and Select positions
	POINT	point11	= {105 - iSize, 65 - iSize};
	m_vecButtonPositions.push_back(point11);

	POINT	point12	= {133 - iSize, 65 - iSize};
	m_vecButtonPositions.push_back(point12);
}
