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

		// Resize client area
		void resizeClientArea();

		// Show mouse
		void showMouse(bool _bShow);
};

ENDNAMESPACE
