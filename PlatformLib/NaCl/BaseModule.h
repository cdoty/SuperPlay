// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include <ppapi/cpp/module.h>
#include <ppapi/cpp/var.h>

class BaseModule : public pp::Module
{
	public:
		// Constructor
		BaseModule();
	
		// Destructor
		virtual ~BaseModule();

		// Init
		virtual bool Init();

		// Create instance
		virtual pp::Instance* CreateInstance(PP_Instance _instance);
};
