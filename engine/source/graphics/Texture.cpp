#include "graphics/Texture.h"
#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace eng
{
	Texture::Texture(int width, int height, int numChannels, unsigned char* data) noexcept
		: m_Width{ width },
		m_Height{ height },
		m_NumChannels{ numChannels }
	{
		Init(width, height, numChannels, data);
	}

	Texture::~Texture() noexcept
	{
		if (m_TextureID > 0)
		{
			glDeleteTextures(1, &m_TextureID);
		}
	}

	void Texture::Init(int width, int height, int numChannels, unsigned char* data)
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
		// mag filter enlarges, use GL_LINEAR for magnification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	shared<Texture> Texture::Load(const std::string& path)
	{
		int width, height, numChannels;

		auto& fs = eng::Engine::GetInstance().GetFileSystem();
		auto fullPath = fs.GetAssetsFolder() / path;

		if (!std::filesystem::exists(fullPath)) return nullptr;

		shared<Texture> result;

		unsigned char* data = stbi_load(fullPath.string().c_str(), &width, &height, &numChannels, 0);
	
		if (data)
		{
			result = std::make_shared<Texture>(width, height, numChannels, data);
			stbi_image_free(data);
		}

		return result;
	}
}
