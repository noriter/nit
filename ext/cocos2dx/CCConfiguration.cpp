#include "nit2d_pch.h"

/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCConfiguration.h"
#include "ccMacros.h"
#include "ccConfig.h"

NS_CC_BEGIN;

CCConfiguration::CCConfiguration(void)
:m_nMaxTextureSize(0) 
, m_nMaxModelviewStackDepth(0)
, m_bSupportsPVRTC(false)
, m_bSupportsNPOT(false)
, m_bSupportsBGRA8888(false)
, m_bSupportsDiscardFramebuffer(false)
, m_bInited(false)
, m_uOSVersion(0)
, m_nMaxSamplesAllowed(0)
, m_pGlExtensions(NULL)
{
}

bool CCConfiguration::init(void)
{
	CCLOG("cocos2d: GL_VENDOR:     %s", glGetString(GL_VENDOR));
	CCLOG("cocos2d: GL_RENDERER:   %s", glGetString(GL_RENDERER));
	CCLOG("cocos2d: GL_VERSION:    %s", glGetString(GL_VERSION));

	m_pGlExtensions = (char *)glGetString(GL_EXTENSIONS);

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_nMaxTextureSize);
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &m_nMaxModelviewStackDepth);

	m_bSupportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	m_bSupportsNPOT = checkForGLExtension("GL_APPLE_texture_2D_limited_npot");
	m_bSupportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	m_bSupportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");

	CCLOG("cocos2d: GL_MAX_TEXTURE_SIZE: %d", m_nMaxTextureSize);
	CCLOG("cocos2d: GL_MAX_MODELVIEW_STACK_DEPTH: %d",m_nMaxModelviewStackDepth);
	CCLOG("cocos2d: GL supports PVRTC: %s", (m_bSupportsPVRTC ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports BGRA8888 textures: %s", (m_bSupportsBGRA8888 ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports NPOT textures: %s", (m_bSupportsNPOT ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports discard_framebuffer: %s", (m_bSupportsDiscardFramebuffer ? "YES" : "NO"));
	
	CCLOG("cocos2d: compiled with NPOT support: %s", "YES");
	CCLOG("cocos2d: compiled with VBO support in TextureAtlas : %s", "YES");

	m_bInited = true;

	return true;
}

CCGlesVersion CCConfiguration::getGlesVersion()
{
	// To get the Opengl ES version
	String strVersion((char *)glGetString(GL_VERSION));
	if ((int)strVersion.find("1.0") != -1)
	{
		return GLES_VER_1_0;
	}
	else if ((int)strVersion.find("1.1") != -1)
	{
		return GLES_VER_1_1;
	}
	else if ((int)strVersion.find("2.0") != -1)
	{
		return GLES_VER_2_0;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	return GLES_VER_2_0;
#else


	return GLES_VER_INVALID;
#endif
}

static CCConfiguration* s_Instance;

CCConfiguration* CCConfiguration::sharedConfiguration(void)
{
	return s_Instance;
}

void CCConfiguration::_setInstance(CCConfiguration* instance)
{
	s_Instance = instance;
}

bool CCConfiguration::checkForGLExtension(const String &searchName)
{
	bool bRet = false;
	const char *kSearchName = searchName.c_str();
	
	if (m_pGlExtensions && 
		strstr(m_pGlExtensions, kSearchName))
	{
		bRet = true;
	}
	
	return bRet;
}

NS_CC_END;
