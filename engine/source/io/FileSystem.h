#pragma once
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <filesystem>

namespace eng
{
	class FileSystem
	{
	public:
		std::filesystem::path GetExecutableFolder() const;
		std::filesystem::path GetAssetsFolder() const;

		std::vector<char> LoadFile(const std::filesystem::path& path);
		std::vector<char> LoadAssetFile(const std::string& relativePath);
		std::string LoadAssetFileText(const std::string& relativePath);
	};
}

#endif // FILESYSTEM_H
