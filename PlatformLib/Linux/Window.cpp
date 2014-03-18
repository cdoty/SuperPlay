// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <SDL2/SDL.h>
#include <GL/glu.h>

#include "GameHeader.h"
#include "Image.h"
#include "Log.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

NAMESPACE(SPlay)

Window::Window()	:
	m_pWindow(NULL),
	m_pRenderer(NULL)
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0)
	{
		Log::instance()->logError("Unable to initialize SDL\n%s", SDL_GetError());

		return	false;
	}

	const GameHeader&	gameHeader	= System::getGameHeader();
	
	bool	bFullscreen	= gameHeader.bFullScreen;

	if (true == bFullscreen)
	{
		SDL_DisplayMode	displayMode;

		if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
		{
			Log::instance()->logError("Unable to get current display mode\n%s", SDL_GetError());
			
			return	false;
		}

		m_iWidth	= displayMode.w;
		m_iHeight	= displayMode.h;
	}

	else
	{
		m_iWidth	= gameHeader.iWindowedWidth;
		m_iHeight	= gameHeader.iWindowedHeight;
	}

	int	iFlags	= SDL_WINDOW_OPENGL;
	
	if (true == gameHeader.bFullScreen)
	{
		iFlags	|= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	else
	{
		iFlags	|= SDL_WINDOW_RESIZABLE;
	}

	if (SDL_CreateWindowAndRenderer(m_iWidth, m_iHeight, iFlags, &m_pWindow, &m_pRenderer) != 0)
	{
		Log::instance()->logError("Unable to create windows and renderer\n%s", SDL_GetError());
			
		return	false;
	}

	if (false == checkRenderer())
	{
		return	false;
	}

	if (true == bFullscreen)
	{
		showMouse(false);
	}

	SDL_SetWindowTitle(m_pWindow, gameHeader.strAppName.c_str());

	// Create app icon
	Image*	pImage	= Image::create("AppIcon.png");

	if (pImage != NULL)
	{
		SDL_Surface*	pIconSurface	= SDL_CreateRGBSurfaceFrom(pImage->getPixels(), pImage->getWidth(), pImage->getHeight(), 32, 
			pImage->getWidth() * 4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

		if (pIconSurface != NULL)
		{
			SDL_SetWindowIcon(m_pWindow, pIconSurface);

			SDL_FreeSurface(pIconSurface);
		}
	
		delete	pImage;
	}

	SDL_DisableScreenSaver();

	return	true;
}

void Window::close()
{
	showMouse(true);

	SDL_EnableScreenSaver();

	if (m_pRenderer != NULL)
	{		
		SDL_DestroyRenderer(m_pRenderer);

		m_pRenderer	= NULL;
	}

	if (m_pWindow != NULL)
	{
		SDL_GL_MakeCurrent(m_pWindow, NULL);

		SDL_DestroyWindow(m_pWindow);

		m_pWindow	= NULL;
	}	

	SDL_Quit();
}

void Window::showMouse(bool _bShow) const
{
	SDL_ShowCursor(true == _bShow ? 1 : 0);
}

bool Window::checkRenderer() const
{
	SDL_RendererInfo	rendererInfo;

	SDL_GetRendererInfo(m_pRenderer, &rendererInfo);

	if (0 == (rendererInfo.flags & SDL_RENDERER_ACCELERATED) || 
		0 == (rendererInfo.flags & SDL_RENDERER_TARGETTEXTURE))
	{
		Log::instance()->logError("Suitable renderer not found");

		return	false;
	}
	
	return	true;
}

ENDNAMESPACE
