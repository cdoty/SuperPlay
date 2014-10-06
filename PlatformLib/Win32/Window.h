// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <windows.h>

#include "Macros.h"

NAMESPACE(SPlay)

class Window
{
	public:
		// Constructor
		Window();

		// Destructor
		~Window();

		// Create
		static Window* create();
		
		// Initialize
		bool initialize();
		
		// Close
		void close();

		// Get layered size
		int getLayeredWidth() const {return m_iLayeredWidth;}
		int getLayeredHeight() const {return m_iLayeredHeight;}

		// Get layered buffer
		uint8_t* getLayeredBuffer() const {return m_pLayeredBuffer;}

		// Draw layered window
		void drawLayeredWindow();

		// Get window handle
		HWND getHwnd() const {return m_hWnd;}
		
		// Get window size
		int getWindowWidth() const {return m_iWidth;}
		int getWindowHeight() const {return m_iHeight;}

		// Message proc
		static LRESULT CALLBACK messageProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	private:
		// App instance
		HINSTANCE	m_hInstance;
		
		// Window handle
		HWND		m_hWnd;

		// Window class atom
		ATOM		m_sClassAtom;

		// Window size
		int			m_iWidth;
		int			m_iHeight;

		// Layered window info
		int			m_iLayeredWidth;
		int			m_iLayeredHeight;
		HDC			m_hLayeredDC;
		HBITMAP		m_hLayeredBitmap;
		BITMAPINFO	m_layeredBitmapInfo;
		uint8_t*	m_pLayeredBuffer;
		uint8_t*	m_pRenderBuffer;

		// Frame
		uint8_t*	m_pFrameBuffer;
		int			m_iFrameWidth;
		int			m_iFrameHeight;
		int			m_iFrameOffset;

		// Resize client area
		void resizeClientArea();

		// Center window
		void centerWindow();

		// Show mouse
		void showMouse(bool _bShow);

		// Load frame
		bool loadFrame();

		// Create layered window
		bool createLayeredWindow();

		// Destroy layered window
		void destroyLayeredWindow();

		// Draw screen
		void drawScreen();

		// Pre-multiply alpha
		void premultiplyAlpha(uint8_t* _pBuffer, int _iWidth, int _iHeight);

		// Update layered window
		void updateLayeredWindow();

		// Get frame point
		void getFramePoint(int& _iX, int& _iY);
};

ENDNAMESPACE
