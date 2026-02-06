#pragma once
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include "graphics/VertexLayout.h"
#include "Core.h"

namespace eng
{
	class Mesh
	{
	public:
		Mesh(const VertexLayout& layout,
			 const List<float>& verticies,
			 const List<uint32_t>& indicies) noexcept;
		Mesh(const VertexLayout&& layout,
			 const List<float>&& verticies) noexcept;

		Mesh(const Mesh&) noexcept = delete;
		Mesh& operator=(const Mesh&) noexcept = delete;

		void Bind();
		void Draw();

	private:
		VertexLayout m_VertexLayout;
		GLuint m_VAO = 0;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;

		size_t m_VertexCount = 0;
		size_t m_IndexCount = 0;
	};
}

#endif // MESH_H
