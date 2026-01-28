#include "render/Mesh.h"
#include "graphics/GraphicsAPI.h"
#include "Engine.h"

namespace eng
{
	Mesh::Mesh(const VertexLayout& layout, 
		const std::vector<float>& verticies, 
		const std::vector<uint32_t>& indicies) noexcept
	{
		m_VertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		// create VBO and EBO
		m_VBO = graphicsAPI.CreateVertexBuffer(verticies);
		m_EBO = graphicsAPI.CreateIndexBuffer(indicies);

		// generate and bind VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		for (auto& element : m_VertexLayout.elements)
		{
			glVertexAttribPointer(
				element.index,
				element.size,
				element.type,
				GL_FALSE,
				m_VertexLayout.stride,
				(void*)(uintptr_t)element.offset
			);
			glEnableVertexAttribArray(element.index);
		}

		// bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		// unbind VAO, VBO, EBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_VertexCount = (verticies.size() * sizeof(float)) / m_VertexLayout.stride;
		m_IndexCount = indicies.size();
	}

	Mesh::Mesh(const VertexLayout&& layout, 
		const std::vector<float>&& verticies) noexcept
	{
		m_VertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		// create VBO
		m_VBO = graphicsAPI.CreateVertexBuffer(verticies);

		// generate and bind VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		for (auto& element : m_VertexLayout.elements)
		{
			glVertexAttribPointer(
				element.index,
				element.size,
				element.type,
				GL_FALSE,
				m_VertexLayout.stride,
				(void*)(uintptr_t)element.offset
			);
			glEnableVertexAttribArray(element.index);
		}

		// unbind VAO, VBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_VertexCount = (verticies.size() * sizeof(float)) / m_VertexLayout.stride;
	}

	void Mesh::Bind()
	{
		glBindVertexArray(m_VAO);
	}

	void Mesh::Draw()
	{
		if (m_IndexCount > 0)
		{
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
		}
	}
}
