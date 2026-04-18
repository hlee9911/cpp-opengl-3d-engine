#pragma once

#include "font/Font.h"

#include <string>

typedef struct FT_LibraryRec_* FT_Library;

namespace eng
{
	class FontManager
	{
	public:
		~FontManager() noexcept;
		void Init();
		shared<Font> GetFont(const std::string& path, int size);

	private:
		FT_Library m_FontLibrary = nullptr;

		// for each font family, we store a map of size to font
		// for one path, we can have many sizes. Thus, family maps size to font instances
		using FontFamily = Dictionary<int, shared<Font>>;

		// top level map
		Dictionary<std::string, FontFamily> m_Fonts;
	};
}
