// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <GLES2/gl2.h>
#include <ppapi/gles2/gl2ext_ppapi.h>

#include "BaseInstance.h"
#include "BaseModule.h"

BaseModule::BaseModule()	:
	pp::Module()
{
}
	
BaseModule::~BaseModule()
{
	glTerminatePPAPI();
}

bool BaseModule::Init()
{
	return	GL_TRUE == glInitializePPAPI(get_browser_interface());
}

pp::Instance* BaseModule::CreateInstance(PP_Instance _instance)
{
	return	new BaseInstance(_instance, this);
}

namespace pp
{
	Module* CreateModule()
	{
		return	new BaseModule();
	}
}
