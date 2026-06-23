#pragma once

#include <GL/glew.h>

#include <glm/vec3.hpp>

#include <string>

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
		void DrawIndexedRange(uint32_t startIndex, uint32_t indexCount);
		void UpdateDynamic(const List<float>& verticies);
		void UpdateDynamic(const List<float>& verticies, const List<uint32_t>& indicies);

		static shared<Mesh> CreateBox(const glm::vec3& extents = glm::vec3(1.0f));
		// static shared<Mesh> Load(const std::string& path);
		
		// stacks and sectors define how smooth the sphere will be
		static shared<Mesh> CreateSphere(float radius, int sectors, int stacks);
		
		static shared<Mesh> CreatePlane();

		static shared<Mesh> CreateCylinder(float radius, float height, int segments);

		static shared<Mesh> CreateCone(float radius, float height, int segments);

	private:
		VertexLayout m_VertexLayout;
		GLuint m_VAO = 0;
		GLuint m_VBO = 0;
		GLuint m_EBO = 0;

		size_t m_VertexCount = 0;
		size_t m_IndexCount = 0;
	};
}
