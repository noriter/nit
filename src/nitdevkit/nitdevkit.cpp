﻿/// nit - Noriter Framework
/// A Cross-platform Open Source Integration for Game-oriented Apps
///
/// http://www.github.com/ellongrey/nit
///
/// Copyright (c) 2013 by Jun-hyeok Jang
/// 
/// (see each file to see the different copyright owners)
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// Author: ellongrey

#include "nitdevkit_pch.h"

#include "nit/app/Plugin.h"

#include "nitdevkit/nitdevkit.h"

NS_NIT_BEGIN;

////////////////////////////////////////////////////////////////////////////////

extern SQRESULT NitLibDevKit(HSQUIRRELVM v);

////////////////////////////////////////////////////////////////////////////////

class NITDEVKIT_API DevKitPlugin : public Plugin
{
public:
	virtual void onInstall()
	{
		Register(new NIT_LIB_ENTRY(NitLibDevKit, "NitLibWxNit"));
	}

	virtual void onUninstall()
	{
	}
};

////////////////////////////////////////////////////////////////////////////////

NIT_PLUGIN_DEFINE(NITDEVKIT_API, DevKitPlugin);

NS_NIT_END;
