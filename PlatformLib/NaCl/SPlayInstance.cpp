#include <GLES2/gl2.h>
#include <ppapi/c/ppb_opengles2.h>
#include <ppapi/cpp/module.h>
#include <ppapi/gles2/gl2ext_ppapi.h>
#include <ppapi_simple/ps_interface.h>

#include "GameHeader.h"
#include "Log.h"
#include "Platform.h"
#include "SPlayInstance.h"
#include "System.h"

NAMESPACE(SPlay)

SPlayInstance::SPlayInstance(PP_Instance _instance)	:
	PSInstance(_instance),
	m_callbackFactory(this)
{
}

void SPlayInstance::DidChangeView(const pp::View& _view)
{
	if (true == m_graphics3D.is_null())
	{
		Log::instance()->logMessage("Create OpenGL context");

		m_pOpenGLES2	= static_cast<const PPB_OpenGLES2*>(pp::Module::Get()->GetBrowserInterface(PPB_OPENGLES2_INTERFACE));

		if (NULL == m_pOpenGLES2)
		{
			Log::instance()->logError("Unable to get OpenGL ES2 interface");

			return;
		}

		Log::instance()->logMessage("Update game header");

		GameHeader&	gameHeader	= System::getUpdateableGameHeader();
	
		const pp::Rect&	viewRect	= _view.GetRect();

		gameHeader.iWindowedWidth	= viewRect.width();
		gameHeader.iWindowedHeight	= viewRect.height();

		int32_t contextAttributes[]	=
		{
			PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 0,
			PP_GRAPHICS3DATTRIB_BLUE_SIZE, 8,
			PP_GRAPHICS3DATTRIB_GREEN_SIZE, 8,
			PP_GRAPHICS3DATTRIB_RED_SIZE, 8,
			PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 0,
			PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 0,
			PP_GRAPHICS3DATTRIB_SAMPLES, 0,
			PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
			PP_GRAPHICS3DATTRIB_WIDTH, gameHeader.iWindowedWidth,
			PP_GRAPHICS3DATTRIB_HEIGHT, gameHeader.iWindowedHeight,
			PP_GRAPHICS3DATTRIB_NONE,
		};
  
		Log::instance()->logMessage("Create graphics 3D");

		m_graphics3D	= pp::Graphics3D(this, contextAttributes);

		if (true == m_graphics3D.is_null())
		{
			Log::instance()->logError("Unable to create Graphics3D");
		
			return;
		}

		Log::instance()->logMessage("Bind graphics");

		if (false == BindGraphics(m_graphics3D))
		{
			glSetCurrentContextPPAPI(0);

			Log::instance()->logError("Unable to bind graphics");
		
			return;
		}

		Log::instance()->logMessage("Set current context");

		glSetCurrentContextPPAPI(m_graphics3D.pp_resource());
	
		Log::instance()->logMessage("Set bound");

		Platform::setBound();
	}

	PSInstance::DidChangeView(_view);
}

void SPlayInstance::callOnMainThread(const PP_CompletionCallback& _callback, int32_t iResult)
{
	PSInterfaceCore()->CallOnMainThread(0, _callback, iResult);
}

ENDNAMESPACE
