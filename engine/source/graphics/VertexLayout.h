#pragma once

#include <GL/glew.h>

#include <vector>
#include <stdint.h>

#include "Core.h"

namespace eng
{
	struct VertexElement
	{
		GLuint index; // Attribute location
		GLuint size; // Number of components (e.g., 3 for vec3)
		GLuint type; // Data type (e.g., GL_FLOAT)
		uint32_t offset; // Offset in bytes from the start of the vertex

		static constexpr int PositionIndex = 0;
		static constexpr int ColorIndex = 1;
		static constexpr int UVIndex = 2;
		static constexpr int NormalIndex = 3;
	};
	
	struct VertexLayout
	{
		List<VertexElement> elements;
		uint32_t stride = 0; // Total size of the single vertex in bytes
	};
}
