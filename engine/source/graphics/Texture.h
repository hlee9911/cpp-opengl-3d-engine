#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

namespace eng
{
	class Texture
	{
	public:
		Texture(int width, int height, int numChannels, unsigned char* data) noexcept;
		~Texture() noexcept;
		GLuint GetID() const noexcept { return m_TextureID; }

	private:
		int m_Width = 0;
		int m_Height = 0;
		int m_NumChannels = 0;
		GLuint m_TextureID = 0;
	};
}

#endif // TEXTURE_H
