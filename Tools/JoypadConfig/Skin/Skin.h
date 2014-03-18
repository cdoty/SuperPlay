#pragma once

#include <windows.h>

#include "Macros.h"

CLASSPTR(Skin)

class Skin
{
	public:
		// Constructor
		Skin();
		
		// Destructor
		~Skin();
		
		// Create
		static SkinPtr create();
		
		// Initialize
		bool initialize();
		
		// Close
		void close();
		
		// Set HWND
		void setHWND(HWND _hWnd) {m_hWnd = _hWnd;}

		// Apply region
		bool applyRegion();
		
		// Get width
		int getWidth() {return m_iWidth;}

		// Get height
		int getHeight() {return m_iHeight;}
	
		// Redraw
		void redraw(HDC _hDC);
		
		// Get DC
		HDC getDC() {return m_hDC;}

	private:
		// Skin size
		int		m_iWidth;
		int		m_iHeight;

		// Windows handle
		HWND	m_hWnd;

		// Device context
		HDC		m_hDC;

		// Bitmap handle
		HBITMAP	m_hBitmap;

		// Old bitmap object
		HBITMAP	m_hOldBitmap;
		
		// Region handle
		HRGN	m_hRegion;
		
		// Load bitmap
		bool loadBitmap();
		
		// Load region
		bool loadRegion();
};