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
#include "Log.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

NAMESPACE(SPlay)

// Window class name
static const char*	gsc_szClassName	= "SPlayWindow";

Window::Window()	:
	m_pDisplay(NULL),
	m_pFBConfig(NULL),
	m_pSDLWindow(NULL)
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
	if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0)
	{
		Log::instance()->logError("Unable to initialize SDL\n%s", SDL_GetError());

		return	false;
	}

	m_pDisplay	= XOpenDisplay(NULL);

	if (NULL == m_pDisplay)
	{
		Log::instance()->logError("Unable to open X display");

		return	false;
	}

	int	iMajor;
	int	iMinor;
	
	if (false == glXQueryVersion(m_pDisplay, &iMajor, &iMinor))
	{
		Log::instance()->logError("Unable to query versopm");

		return	false;
	}
	
	if (iMajor < 1 || (1 == iMajor && iMinor < 3))
	{
		return	false;
	}

	int	iTemp;
	
	if (false == glXQueryExtension(m_pDisplay, &iTemp, &iTemp))
	{
		Log::instance()->logError("Unable to query extension");

		return	false;
	}

	int	iVisualAttribs[]  =
	{
		GLX_X_RENDERABLE, True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DOUBLEBUFFER, True,
		None
	};

	int	iCount	= 0;
	
	// Choose framebuffer config
	m_pFBConfig	= glXChooseFBConfig(m_pDisplay, DefaultScreen(m_pDisplay), iVisualAttribs, &iCount);
	
	if (NULL == m_pFBConfig)
	{
		Log::instance()->logError("Unable to get famebuffer config.");

		return	false;
	}

	// Get visual info
	XVisualInfo*	pVisualInfo	= glXGetVisualFromFBConfig(m_pDisplay, m_pFBConfig[0]);
	
	if (NULL == pVisualInfo)
	{
		Log::instance()->logError("Unable to get visual from framebuffer config.");

		return	false;
	}
	
	XSetWindowAttributes	windowAttributes;
	
	// Create colormap
	m_colormap = XCreateColormap(m_pDisplay, RootWindow(m_pDisplay, pVisualInfo->screen), 
		pVisualInfo->visual, AllocNone);
		
	windowAttributes.colormap			= m_colormap;
	windowAttributes.background_pixmap	= None;
	windowAttributes.border_pixel		= 0;
	windowAttributes.event_mask			= StructureNotifyMask;
	
	const GameHeader&	gameHeader	= System::getGameHeader();
	
	bool	bFullscreen	= gameHeader.bFullScreen;

	if (false == bFullscreen)
	{
		// Create window
		m_window	= XCreateWindow(m_pDisplay, RootWindow(m_pDisplay, pVisualInfo->screen), 0, 0, 
			gameHeader.iWindowedWidth, gameHeader.iWindowedHeight, 0, pVisualInfo->depth, InputOutput,
			pVisualInfo->visual, CWBorderPixel | CWColormap | CWEventMask, &windowAttributes);
		
		resizeClientArea();
	}
	
	else
	{
	}

	XFree(pVisualInfo);
	
	if (0 == m_window)
	{
		Log::instance()->logError("Unable to create window.");
		
		return	false;
	}
	
	// Set window name
	XStoreName(m_pDisplay, m_window, gameHeader.strAppName.c_str());
	
	// Show window
	XMapWindow(m_pDisplay, m_window);
	
	return	true;
}

void Window::close()
{
	if (m_pSDLWindow != NULL)
	{
		SDL_SetWindowGrab(m_pSDLWindow, SDL_FALSE);
		
		SDL_DestroyWindow(m_pSDLWindow);
	}
	
	XDestroyWindow(m_pDisplay, m_window);
	XFreeColormap(m_pDisplay, m_colormap);
	XCloseDisplay(m_pDisplay);

	SDL_Quit();
}

void Window::resizeClientArea()
{
}

ENDNAMESPACE
