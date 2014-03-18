// Window - Class representing the window
//
// © 2011 Raster Software. All rights reserved.

#pragma once

#include <vector>

#include "Macros.h"
#include "Skin.h"

CLASSPTR(Window)

class Window
{
	public:
		// Constructor
		Window();

		// Destructor
		~Window();

		// Create
		static WindowPtr create();
		
		// Initialize
		bool initialize();
		
		// Close
		void close();

		// Run
		void run();

		// Get skin
		SkinPtr getSkin() {return m_pSkin;}

		// Get window handle
		HWND getHwnd() {return m_hWnd;}
		
		// Get device context
		HDC getDC() {return GetDC(m_hWnd);}

		// Get input
		int getInput() {return m_iInput;}

		// Set input
		void setInput(int _iInput);

		// Get button position
		POINT getButtonPosition(int _iInput) {return m_vecButtonPositions[_iInput];}

		// Message proc
		static LRESULT CALLBACK messageProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

	private:
		// App instance
		HINSTANCE		m_hInstance;
		
		// Window handle
		HWND			m_hWnd;
						
		// Window class atom
		ATOM			m_sClassAtom;

		// Skin
		SkinPtr			m_pSkin;

		// Input position
		int				m_iInput;

		// Button positions
		std::vector<POINT>	m_vecButtonPositions;

		// Set button positions
		void setButtonPositions();
};
