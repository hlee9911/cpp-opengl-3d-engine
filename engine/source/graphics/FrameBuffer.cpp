#include "graphics/FrameBuffer.h"

namespace eng
{
    FrameBuffer::FrameBuffer() noexcept
    {

    }

	FrameBuffer::~FrameBuffer() noexcept
	{
		Destroy();
	}

	bool FrameBuffer::Init(int width, int height)
	{
		m_Width = width;
		m_Height = height;

		// Create framebuffer
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		// Color Texture
		glGenTextures(1, &m_ColorTexture);
		glBindTexture(GL_TEXTURE_2D, m_ColorTexture);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA8,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			nullptr);

		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,
			GL_LINEAR);

		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,
			GL_LINEAR);

		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			m_ColorTexture,
			0);

		// Depth / Stencil Buffer
		glGenRenderbuffers(
			1,
			&m_DepthStencilRBO);

		glBindRenderbuffer(
			GL_RENDERBUFFER,
			m_DepthStencilRBO);

		glRenderbufferStorage(
			GL_RENDERBUFFER,
			GL_DEPTH24_STENCIL8,
			width,
			height);

		glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER,
			m_DepthStencilRBO);

		// Validation
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Logger::Error("Framebuffer creation failed");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	void FrameBuffer::Destroy()
	{
		if (m_DepthStencilRBO)
		{
			glDeleteRenderbuffers(1, &m_DepthStencilRBO);
			m_DepthStencilRBO = 0;
		}

		if (m_ColorTexture)
		{
			glDeleteTextures(1, &m_ColorTexture);
			m_ColorTexture = 0;
		}

		if (m_FBO)
		{
			glDeleteFramebuffers(1, &m_FBO);
			m_FBO = 0;
		}
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool FrameBuffer::Resize(
		int width,
		int height)
	{
		if (width <= 0 || height <= 0)
		{
			return false;
		}

		if (width == m_Width && height == m_Height)
		{
			return true;
		}

		Destroy();

		return Init(width, height);
	}

}
