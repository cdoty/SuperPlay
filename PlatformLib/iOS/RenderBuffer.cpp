// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#include <OpenGLES/ES1/glext.h>

#include "Log.h"
#include "RenderBuffer.h"

NAMESPACE(SPlay)

RenderBuffer::RenderBuffer()	:
	m_uFrameBuffer(GL_INVALID_VALUE),
	m_uRenderBuffer(GL_INVALID_VALUE)
{
	glGenRenderbuffersOES(1, &m_uRenderBuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_uRenderBuffer);
}

RenderBuffer::~RenderBuffer()
{
	close();
}

bool RenderBuffer::initialize()
{
	glGenFramebuffersOES(1, &m_uFrameBuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uFrameBuffer);

	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_uRenderBuffer);

	GLenum error	= glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES);

	if (error != GL_FRAMEBUFFER_COMPLETE_OES)
	{
		SPlay::Log::instance()->logError("Unable to create frame and render buffers (%d)", error);

		return	false;
	}

	return	true;
}

void RenderBuffer::close()
{
	if (m_uFrameBuffer != GL_INVALID_VALUE)
	{
		glDeleteFramebuffersOES(1, &m_uFrameBuffer);

		m_uFrameBuffer	= GL_INVALID_VALUE;
	}

	if (m_uRenderBuffer != GL_INVALID_VALUE)
	{
		glDeleteRenderbuffersOES(1, &m_uRenderBuffer);

		m_uRenderBuffer	= GL_INVALID_VALUE;
	}
}

void RenderBuffer::bindFrameBuffer()
{
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uFrameBuffer);
}

void RenderBuffer::bindRenderBuffer()
{
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_uRenderBuffer);
}

ENDNAMESPACE
