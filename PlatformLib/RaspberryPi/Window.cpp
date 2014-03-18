// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <bcm_host.h>

#include "GameHeader.h"
#include "Log.h"
#include "Platform.h"
#include "PlatformDefines.h"
#include "System.h"
#include "Window.h"

NAMESPACE(SPlay)

Window::Window()	:
	m_pDisplay(EGL_NO_DISPLAY),
	m_pSurface(EGL_NO_SURFACE),
	m_pContext(EGL_NO_CONTEXT),
	m_pSDLWindow(NULL)
{
}

Window::~Window()
{
	close();
}

Window* Window::create()
{
	if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0)
	{
		Log::instance()->logError("Unable to initialize SDL\n%s", SDL_GetError());

		return	false;
	}

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
	bcm_host_init();
	
	m_pSDLWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, 0);

	if (NULL == m_pSDLWindow)
	{
		return	false;
	}

	m_pDisplay	= eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if (EGL_NO_DISPLAY == m_pDisplay)
	{
		Log::instance()->logError("Unable to get display %d", eglGetError());

		return	false;
	}

	EGLint	iMajor;
	EGLint	iMinor;

	if (EGL_FALSE == eglInitialize(m_pDisplay, &iMajor, &iMinor))
	{
		Log::instance()->logError("Unable to initialize EGL %d", eglGetError());

		return	false;
	}

	EGLint iConfigAttributes[]	=
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
 		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	EGLConfig	config;
	int			iConfigs;

	if (EGL_FALSE == eglChooseConfig(m_pDisplay, iConfigAttributes, &config, 1, &iConfigs))
	{
		Log::instance()->logError("Unable to choose config %d", eglGetError());

		return	false;
	}

	m_pContext	= eglCreateContext(m_pDisplay, config, EGL_NO_CONTEXT, NULL);

	if (EGL_NO_CONTEXT == m_pContext)
	{
		Log::instance()->logError("Unable to create context %d", eglGetError());

		return	false;
	}

    uint32_t iMaxWidth	= 0;
	uint32_t iMaxHeight	= 0;
	
	if (graphics_get_display_size(0, &iMaxWidth, &iMaxHeight) < 0)
	{
		Log::instance()->logError("Unable to get display size");
		
		return	false;
	}
	
#if SCALED_DISPLAY
	const GameHeader&	gameHeader	= System::getGameHeader();

	VC_RECT_T	src;

	src.x		= 0;
	src.y		= 0;
	src.width	= gameHeader.iScreenWidth << 16;
	src.height	= gameHeader.iScreenHeight << 16;        

	VC_RECT_T	dest;
	
	dest.x		= 0;
	dest.y		= 0;
	dest.width	= iMaxWidth;
	dest.height	= iMaxHeight;
	  
	DISPMANX_ELEMENT_HANDLE_T	element;
	DISPMANX_DISPLAY_HANDLE_T	display;
	DISPMANX_UPDATE_HANDLE_T	update;
	
	display	= vc_dispmanx_display_open(0);
	update	= vc_dispmanx_update_start(0);		 
	element	= vc_dispmanx_element_add(update, display, 0, &dest, 0, &src, DISPMANX_PROTECTION_NONE, NULL, NULL, 
		DISPMANX_NO_ROTATE);
	  
	m_window.element	= element;
	m_window.width		= gameHeader.iScreenWidth;
	m_window.height		= gameHeader.iScreenHeight;

	vc_dispmanx_update_submit_sync(update);
      
	m_pSurface	= eglCreateWindowSurface(m_pDisplay, config, &m_window, NULL);

	if (EGL_NO_SURFACE == m_pSurface)
	{
		Log::instance()->logError("Unable to create window surface %d", eglGetError());

		return	false;
	}

	if (EGL_FALSE == eglMakeCurrent(m_pDisplay, m_pSurface, m_pSurface, m_pContext))
	{
		Log::instance()->logError("Unable to set current context %d", eglGetError());

		return	false;
    }
#else
	VC_RECT_T	src;

	src.x		= 0;
	src.y		= 0;
	src.width	= iMaxWidth;
	src.height	= iMaxHeight;

	VC_RECT_T	dest;
	
	dest.x		= 0;
	dest.y		= 0;
	dest.width	= iMaxWidth;
	dest.height	= iMaxHeight;
	  
	DISPMANX_ELEMENT_HANDLE_T	element;
	DISPMANX_DISPLAY_HANDLE_T	display;
	DISPMANX_UPDATE_HANDLE_T	update;
	
	display	= vc_dispmanx_display_open(0);
	update	= vc_dispmanx_update_start(0);		 
	element	= vc_dispmanx_element_add(update, display, 0, &dest, 0, &src, DISPMANX_PROTECTION_NONE, NULL, NULL, 
		DISPMANX_NO_ROTATE);
	  
	m_window.element	= element;
	m_window.width		= iMaxWidth;
	m_window.height		= iMaxHeight;

	vc_dispmanx_update_submit_sync(update);
      
	m_pSurface	= eglCreateWindowSurface(m_pDisplay, config, &m_window, NULL);

	if (EGL_NO_SURFACE == m_pSurface)
	{
		Log::instance()->logError("Unable to create window surface %d", eglGetError());

		return	false;
	}

	if (EGL_FALSE == eglMakeCurrent(m_pDisplay, m_pSurface, m_pSurface, m_pContext))
	{
		Log::instance()->logError("Unable to set current context %d", eglGetError());

		return	false;
    }

	const GameHeader&	gameHeader	= System::getUpdateableGameHeader();
    
	gameHeader.iScreenWidth		= iMaxWidth;
	gameHeader.iScreenHeight	= iMaxHeight;
#endif
    
	// Set swap interval
	if (EGL_FALSE == eglSwapInterval(m_pDisplay, 1))
	{
		Log::instance()->logError("Unable to set swap interval context");
	}

	return	true;
}

void Window::close()
{
	if (m_pSDLWindow != NULL)
	{
		SDL_DestroyWindow(m_pSDLWindow);

		m_pSDLWindow	= NULL;
	}

	if (m_pDisplay != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_pDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		
		if (m_pContext != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_pContext, m_pContext);
		
			m_pContext	= EGL_NO_CONTEXT;
		}

		if (m_pSurface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_pDisplay, m_pSurface);
			
			m_pSurface	= EGL_NO_SURFACE;
		}

		eglTerminate(m_pDisplay);
		
		m_pDisplay	= EGL_NO_DISPLAY;
	}

	bcm_host_deinit();
}

ENDNAMESPACE
