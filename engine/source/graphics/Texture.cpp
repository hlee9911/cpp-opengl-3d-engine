#include "graphics/Texture.h"

namespace eng
{
	Texture::Texture(int width, int height, int numChannels, unsigned char* data) noexcept
		: m_Width{ width },
		m_Height{ height },
		m_NumChannels{ numChannels }
	{
		glGenTextures(1, &m_TextureID); // create texture
		glBindTexture(GL_TEXTURE_2D, m_TextureID); // actviate the texture

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
		glGenerateMipmap(GL_TEXTURE_2D); // mipmaps are smaller version of the same texture down to 1 x 1
	
		// wrapping texture if goes out of uv bound
		// s and t here are same as u and v
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// filtering
		// min filter shrinks
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// maag filter enlarges, use GL_LINEAR for magnification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Texture::~Texture() noexcept
	{
		if (m_TextureID > 0)
		{
			glDeleteTextures(1, &m_TextureID);
		}
	}
}
