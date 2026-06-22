#pragma once

#include <GL/glew.h>

#include <string>

#include <sol/sol.hpp>
#include <sol/forward.hpp>

#include "Core.h"

namespace eng
{
	class Texture
	{
	public:
		Texture(int width, int height, int numChannels, unsigned char* data) noexcept;
		~Texture() noexcept;
		GLuint GetID() const noexcept { return m_TextureID; }
		void Init(int width, int height, int numChannels, unsigned char* data);

		const int GetWidth() const noexcept { return m_Width; }
		const int GetHeight() const noexcept { return m_Height; }

		static shared<Texture> Load(const std::string& path);

	private:
		int m_Width = 0;
		int m_Height = 0;
		int m_NumChannels = 0;
		GLuint m_TextureID = 0;
	};

	class TextureManager
	{
	public:
		shared<Texture> GetOrLoadTexture(const std::string& path);

	private:
		Dictionary<std::string, shared<Texture>> m_Textures;
	};
}
