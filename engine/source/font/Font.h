#pragma once

#include "graphics/Texture.h"
#include "Core.h"

namespace eng
{
	struct GlyphDescription
	{
		int x0 = 0, y0 = 0;
		int x1 = 0, y1 = 0;

		int width = 0;
		int height = 0;

		int advance = 0;
		int xOffset = 0;
		int yOffset = 0;
	};

	class Font
	{
	public:
		int GetSize() const noexcept { return m_Size; }
		const GlyphDescription& GetGlyphDescription(char asciiCode) const { return m_Descriptions[static_cast<unsigned char>(asciiCode)]; }
		const shared<Texture>& GetTexture() const { return m_Texture; }

	private:
		int m_Size = 0;
		GlyphDescription m_Descriptions[128]; // using ASCII for now, so 128 characters should be enough
		shared<Texture> m_Texture;

		friend class FontManager;
	};
}
