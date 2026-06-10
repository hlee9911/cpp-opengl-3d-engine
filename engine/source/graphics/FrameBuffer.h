#pragma once

#include "Core.h"

#include <GL/glew.h>

namespace eng
{
    class FrameBuffer
    {
	public:
		FrameBuffer() noexcept;
		~FrameBuffer() noexcept;

		bool Init(int width, int height);
		void Destroy();

		void Bind();
		void Unbind();

		bool Resize(int width, int height);

		GLuint GetColorTexture() const noexcept { return m_ColorTexture; }
		int GetWidth() const noexcept { return m_Width; }
		int GetHeight() const noexcept { return m_Height; }

	private:
		GLuint m_FBO = 0;
		GLuint m_ColorTexture = 0;
		GLuint m_DepthStencilRBO = 0;

		int m_Width = 0;
		int m_Height = 0;
    };
}
