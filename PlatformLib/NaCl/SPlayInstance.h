#pragma once

#include <ppapi/c/ppb_opengles2.h>
#include <ppapi/cpp/graphics_3d.h>
#include <ppapi/cpp/graphics_3d_client.h>
#include <ppapi/utility/completion_callback_factory.h>
#include <ppapi_simple/ps_instance.h>

#include "Macros.h"

NAMESPACE(SPlay)

class SPlayInstance : public PSInstance
{
	public:
		// Constructor
		SPlayInstance(PP_Instance _instance);

		// Did change view hanlder
		virtual void DidChangeView(const pp::View& _view);

		// Call on main thread
		void callOnMainThread(const PP_CompletionCallback& _callback, int32_t iResult = 0);
						
	private:
		// Graphics 3D
		pp::Graphics3D			m_graphics3D;

		// OpenGL ES2 interface
		const PPB_OpenGLES2*	m_pOpenGLES2;

		// Creation callback
		pp::CompletionCallbackFactory<SPlayInstance>	m_callbackFactory;
};

ENDNAMESPACE
