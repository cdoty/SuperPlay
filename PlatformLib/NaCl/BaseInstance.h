// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <pthread.h>
#include <ppapi/c/ppb_opengles2.h>
#include <ppapi/cpp/graphics_3d.h>
#include <ppapi/cpp/graphics_3d_client.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>
#include <ppapi/cpp/var.h>
#include <ppapi/utility/completion_callback_factory.h>

class BaseInstance : public pp::Instance, public pp::Graphics3DClient
{
	public:
		// Constructor
		explicit BaseInstance(PP_Instance _instance, pp::Module* m_pModule);
	
		// Destructor
		virtual ~BaseInstance();

		// Called by the browser when the NaCl module is loaded and all ready to go.
		virtual bool Init(uint32_t _uArgC, const char* _szArgN[], const char* _szArgV[]);

		// Start
		void Start();

		// Called whenever the in-browser window changes size.
		virtual void DidChangeView(const pp::Rect& _rctPosition, const pp::Rect& _rctClip);

		// Context lost
		virtual void Graphics3DContextLost();

		// Handle input event
		virtual bool HandleInputEvent(const pp::InputEvent& _event);

	private:
		// Module
		pp::Module*				m_pModule;

		// Graphics 3D
		pp::Graphics3D*			m_pGraphics3D;

		// OpenGL ES2 interface
		const PPB_OpenGLES2*	m_pOpenGLES2;

		// Display size
		pp::Size				m_displaySize;

		// Render
		bool					m_bRender;

		// Message thread handle
		pthread_t				m_hMessageThread;

		// Creation callback
		pp::CompletionCallbackFactory<BaseInstance> m_callbackFactory;

		// Initialize OpenGL
		void initializeOpenGL(int32_t _iResult);

		// Close OpenGL
		void closeOpenGL();

		// Update
		void update(int32_t _iResult);

		// Preload files
		bool setupFileIO();
};
