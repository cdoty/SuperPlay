// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <GLES2/gl2.h>
#include <nacl_io/nacl_io.h>
#include <ppapi/c/ppb_messaging.h>
#include <ppapi/cpp/input_event.h>
#include <ppapi/gles2/gl2ext_ppapi.h>
#include <sys/mount.h>

#include "AssertLog.h"
#include "BaseInstance.h"
#include "Log.h"
#include "Platform.h"
#include "System.h"
#include "Timer.h"

BaseInstance::BaseInstance(PP_Instance _instance, pp::Module* _module)	:
	pp::Instance(_instance),
	pp::Graphics3DClient(this),
	m_pModule(_module),
	m_pGraphics3D(NULL),
	m_callbackFactory(this),
	m_bRender(false)
{
	SPlay::Platform::setInstance(_instance);

	RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE);
	RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);

	m_pOpenGLES2	= static_cast<const PPB_OpenGLES2*>(_module->GetBrowserInterface(PPB_OPENGLES2_INTERFACE));
}

BaseInstance::~BaseInstance()
{
}

bool BaseInstance::Init(uint32_t _uArgC, const char* _szArgN[], const char* _szArgV[])
{
	if (false == setupFileIO())
	{
		return	false;
	}

	return	true;
}

void BaseInstance::Start()
{
	if (true == SPlay::System::initialize())
	{
		SPlay::Platform::getTimer()->start();
	}
}

void BaseInstance::DidChangeView(const pp::Rect& _rctPosition, const pp::Rect& _rctClip)
{
	if (_rctPosition.width() != 0 && _rctPosition.height() != 0)
	{
		m_displaySize	= _rctPosition.size();
	
		initializeOpenGL(0);
	}
}

void BaseInstance::Graphics3DContextLost()
{
	delete	m_pGraphics3D;
		
	m_pGraphics3D	= NULL;

	pp::CompletionCallback callBack	= m_callbackFactory.NewCallback(&BaseInstance::initializeOpenGL);
	
	m_pModule->core()->CallOnMainThread(0, callBack, 0);
}

bool BaseInstance::HandleInputEvent(const pp::InputEvent& _event)
{
	switch (_event.GetType())
	{
		case PP_INPUTEVENT_TYPE_UNDEFINED:
			break;

		case PP_INPUTEVENT_TYPE_MOUSEDOWN:
			break;

		case PP_INPUTEVENT_TYPE_MOUSEUP:
			break;

		case PP_INPUTEVENT_TYPE_MOUSEMOVE:
			break;

		case PP_INPUTEVENT_TYPE_MOUSEENTER:
			break;

		case PP_INPUTEVENT_TYPE_MOUSELEAVE:
			break;

		case PP_INPUTEVENT_TYPE_WHEEL:
			break;

		case PP_INPUTEVENT_TYPE_RAWKEYDOWN:
			break;

		case PP_INPUTEVENT_TYPE_KEYDOWN:
			break;

		case PP_INPUTEVENT_TYPE_KEYUP:
			break;

		case PP_INPUTEVENT_TYPE_CHAR:
			break;

		case PP_INPUTEVENT_TYPE_CONTEXTMENU:
			break;

		default:
			return	false;
	}

	return	true;
}

void BaseInstance::initializeOpenGL(int32_t _iResult)
{
	ASSERT_LOG(m_displaySize.width() > 0 && m_displaySize.height() > 0, "Invalid width or height");

	int32_t arrContextAttributes[]	=
	{
		PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 0,
		PP_GRAPHICS3DATTRIB_BLUE_SIZE, 8,
		PP_GRAPHICS3DATTRIB_GREEN_SIZE, 8,
		PP_GRAPHICS3DATTRIB_RED_SIZE, 8,
		PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 0,
		PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 0,
		PP_GRAPHICS3DATTRIB_SAMPLES, 0,
		PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
		PP_GRAPHICS3DATTRIB_WIDTH, m_displaySize.width(),
		PP_GRAPHICS3DATTRIB_HEIGHT, m_displaySize.height(),
		PP_GRAPHICS3DATTRIB_NONE,
	};
  
	m_pGraphics3D	= new pp::Graphics3D(this, arrContextAttributes);

	if (true == m_pGraphics3D->is_null())
	{
		ASSERT_LOG(false, "Unable to create Graphics3D");
		
		return;
	}

	if (false == BindGraphics(*m_pGraphics3D))
	{
		ASSERT_LOG(false, "Unable to bind graphics");
		
		return;
	}

	glSetCurrentContextPPAPI(m_pGraphics3D->pp_resource());

	update(0);
}

void BaseInstance::closeOpenGL()
{
	glSetCurrentContextPPAPI(NULL);
}

void BaseInstance::update(int32_t _iResult)
{
	if (_iResult != 0 || NULL == m_pGraphics3D)
	{
		return;
	}

	if (true == m_bRender)
	{
	}

	else
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	pp::CompletionCallback callBack	= m_callbackFactory.NewCallback(&BaseInstance::update);

	m_pGraphics3D->SwapBuffers(callBack);
}

bool BaseInstance::setupFileIO()
{
	SPlay::Log::instance()->logMessage("setupFileIO");

	nacl_io_init_ppapi(pp_instance(), pp::Module::Get()->get_browser_interface());

	mount("NaCl", "/", "httpfs", 0, "");
	
	/* Function name was found, call it. */
	FILE*	pHandle	= fopen("SoundsEvents.xml", "rb");
	
#if 0
	if (NULL == pHandle)
	{
		SPlay::Log::instance()->logError("Unable to open file");
	}

	else
	{
		fclose(pHandle);
	}
#endif

	return	true;
}
