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
		std::filesystem::path GetAssetFolder() const;
	};
}

#endif // FILESYSTEM_H
