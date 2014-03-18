#include "Log.h"
#include "Skin.h"
#include "..\resource.h"

Skin::Skin()	:
	m_hBitmap(NULL),
	m_hRegion(NULL)
{
}

Skin::~Skin()
{
	close();
}

SkinPtr Skin::create()
{
	SkinPtr	pSkin(new Skin());

	if (false == pSkin->initialize())
	{
		pSkin.reset();
	}
	
	return	pSkin;
}

bool Skin::initialize()
{
	if (false == loadBitmap())
	{
		return	false;
	}
	
	if (false == loadRegion())
	{
		return	false;
	}
	
	return	true;
}

void Skin::close()
{
	if (m_hDC != NULL)
	{
		if (m_hOldBitmap != NULL)
		{
			SelectObject(m_hDC, m_hOldBitmap);
			
			m_hOldBitmap	= NULL;
		}
	
		DeleteObject(m_hDC);
		
		m_hDC	= NULL;
	}

	if (m_hBitmap != NULL)
	{
		DeleteObject(m_hBitmap);
		
		m_hBitmap	= NULL;
	}

	if (m_hRegion != NULL)
	{
		// Remove region
		SetWindowRgn(m_hWnd, NULL, true);
		
		DeleteObject(m_hRegion);
		
		m_hRegion	= NULL;
	}
}

bool Skin::applyRegion()
{
	// Apply region
	if (0 == SetWindowRgn(m_hWnd, m_hRegion, true))
	{
		Log::instance()->logError("Unable to apply region to window (%08X)", GetLastError());

		return	false;
	}

	return	true;
}

void Skin::redraw(HDC _hDC)
{
	if (m_hDC != NULL)
	{
		BitBlt(_hDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);
	}
}

bool Skin::loadBitmap()
{
	if (m_hBitmap != NULL)
	{
		DeleteObject(m_hBitmap);
	}
	
	HINSTANCE	hInstance	= GetModuleHandle(NULL);
	
	// Load bitmap resource, width must be a multiple of 4.
	m_hBitmap	= LoadBitmap(hInstance, MAKEINTRESOURCE(BITMAP_SKIN));
	
	BITMAP	bitmap;
	
	if (0 == GetObject(m_hBitmap, sizeof(BITMAP), static_cast<LPVOID>(&bitmap)))
	{
		Log::instance()->logError("Unable to get window skin bitmap object (%08X)", GetLastError());

		return	false;
	}
	
	m_hDC	= CreateCompatibleDC(NULL);
	
	if (NULL == m_hDC)
	{
		Log::instance()->logError("Unable to create compatible DC (%08X)", GetLastError());
	}

	m_hOldBitmap	= static_cast<HBITMAP>(SelectObject(m_hDC, m_hBitmap));

	m_iWidth	= bitmap.bmWidth;
	m_iHeight	= bitmap.bmHeight;

	return	true;
}

bool Skin::loadRegion()
{
	HINSTANCE	hInstance	= GetModuleHandle(NULL);
	
	HRSRC	hResource	= FindResource(hInstance, MAKEINTRESOURCE(REGION_SKIN), "BINARY");
	
	if (NULL == hResource)
	{
		Log::instance()->logError("Unable to load window region object (%08X)", GetLastError());

		return	false;
	}
	
	LPRGNDATA	pRegionData	= static_cast<LPRGNDATA>(LoadResource(hInstance, hResource));
	
	if (NULL == pRegionData)
	{
		Log::instance()->logError("Unable to load window region data (%08X)", GetLastError());

		return	false;
	}
	
	m_hRegion	= ExtCreateRegion(NULL, SizeofResource(NULL, hResource), pRegionData);
	
	if (NULL == m_hRegion)
	{
		Log::instance()->logError("Unable to create window region (%08X)", GetLastError());

		return	false;
	}
	
	FreeResource(pRegionData);
	
	return	true;
}
