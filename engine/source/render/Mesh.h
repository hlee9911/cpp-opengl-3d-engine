#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/vec3.hpp>

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
		Mesh(const VertexLayout& layout,
			 const List<float>& verticies) noexcept;

		Mesh(const Mesh&) noexcept = delete;
		Mesh& operator=(const Mesh&) noexcept = delete;

		void Bind();
		void Unbind();
		void Draw();

		static shared<Mesh> CreateBox(const glm::vec3& extents = glm::vec3(1.0f));
		// static shared<Mesh> Load(const std::string& path);
		
		// stacks and sectors define how smooth the sphere will be
		static shared<Mesh> CreateSphere(float radius, int sectors, int stacks);

	private:
		VertexLayout m_VertexLayout;
		GLuint m_VAO = 0;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;

		size_t m_VertexCount = 0;
		size_t m_IndexCount = 0;
	};
}
