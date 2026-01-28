#pragma once
#ifndef VERTEXLAYOUT_H
#define VERTEXLAYOUT_H

#include <GL/glew.h>

#include <vector>
#include <stdint.h>

namespace eng
{
	struct VertexElement
	{
		GLuint index; // Attribute location
		GLuint size; // Number of components (e.g., 3 for vec3)
		GLuint type; // Data type (e.g., GL_FLOAT)
		uint32_t offset; // Offset in bytes from the start of the vertex
	};
	
	struct VertexLayout
	{
		std::vector<VertexElement> elements;
		uint32_t stride = 0; // Total size of the single vertex in bytes
	};
}

#endif //VERTEXLAYOUT_H
