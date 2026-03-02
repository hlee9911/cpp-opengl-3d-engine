#pragma once

#include <stdio.h>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace eng
{
	// Smart pointer aliases
	template <typename T>
	using unique = std::unique_ptr<T>;

	template <typename T>
	using shared = std::shared_ptr<T>;

	template <typename T>
	using weak = std::weak_ptr<T>;

	// basic templates for containers
	template <typename T>
	using List = std::vector<T>;

	template <typename keyType, typename valType, typename pr = std::less<keyType>>
	using Map = std::map<keyType, valType, pr>; // predicate defaults to std::less, which is ascending order

	template <typename keyType, typename valType, typename hasher = std::hash<keyType>>
	using Dictionary = std::unordered_map<keyType, valType, hasher>;

	template <typename T>
	using Set = std::unordered_set<T>;

	using uint8 = unsigned char;

	// Simple logging macro, ... means variadic arguments
	#define LOG(M, ...) printf("[LOG] " M "\n", ##__VA_ARGS__)
	#define WARN(M, ...) printf("[WARN] " M "\n", ##__VA_ARGS__)
	#define ERROR(M, ...) printf("[ERROR] " M "\n", ##__VA_ARGS__)
}
