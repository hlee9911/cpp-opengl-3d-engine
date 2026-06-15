#include "render/Mesh.h"
#include "graphics/GraphicsAPI.h"
#include "Engine.h"

//#define CGLTF_IMPLEMENTATION
//#include <cgltf.h>

namespace eng
{
	Mesh::Mesh(const VertexLayout& layout, 
		const List<float>& verticies,
		const List<uint32_t>& indicies) noexcept
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

	Mesh::Mesh(const VertexLayout& layout, 
		const List<float>& verticies) noexcept
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

	void Mesh::Unbind()
	{
		glBindVertexArray(0);
	}

	void Mesh::Draw()
	{
		if (m_IndexCount > 0)
		{
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_IndexCount), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_VertexCount));
		}
	}

	void Mesh::DrawIndexedRange(uint32_t startIndex, uint32_t indexCount)
	{
		if (indexCount == 0) return;

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), 
			GL_UNSIGNED_INT,
			reinterpret_cast<void*>(static_cast<size_t>(startIndex) * sizeof(uint32_t)));
	}

	// reupload mesh data each frame
	void Mesh::UpdateDynamic(const List<float>& verticies)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_VertexCount = (verticies.size() * sizeof(float)) / m_VertexLayout.stride;
	}

	void Mesh::UpdateDynamic(const List<float>& verticies, const List<uint32_t>& indicies)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_VertexCount = (verticies.size() * sizeof(float)) / m_VertexLayout.stride;

		if (m_EBO == 0)
		{
			Engine::GetInstance().GetGraphicsAPI().CreateIndexBuffer(indicies);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		m_IndexCount = indicies.size();
	}

	/// <summary>
	/// Creates a box mesh with the specified extents (width, height, depth). The box is centered at the origin and 
	/// extends in both positive and negative directions along each axis based on the extents provided
	/// </summary>
	/// <param name="extents"></param>
	/// <returns></returns>
	shared<Mesh> Mesh::CreateBox(const glm::vec3& extents)
	{
		const glm::vec3 half = extents * 0.5f;
		std::vector<float> verticies =
		{
			// Front face
			// positions        // colors		    // uvs		// normals
			half.x,  half.y, half.z,  1.0f, 0.0f, 0.0f,  extents.x, extents.y,  0.0f, 0.0f, 1.0f,
			-half.x, half.y, half.z,  0.0f, 1.0f, 0.0f,  0.0f, extents.y,	0.0f, 0.0f, 1.0f,
			-half.x, -half.y, half.z,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
			half.x, -half.y, half.z,  1.0f, 1.0f, 0.0f,  extents.x, 0.0f,	0.0f, 0.0f, 1.0f,

			// Top face
			half.x,  half.y, -half.z,  1.0f, 0.0f, 0.0f,  extents.x, extents.z,  0.0f, 1.0f, 0.0f,
			-half.x, half.y, -half.z,  0.0f, 1.0f, 0.0f,  0.0f, extents.z,  0.0f, 1.0f, 0.0f,
			-half.x, half.y, half.z,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
			half.x, half.y, half.z,  1.0f, 1.0f, 0.0f,   extents.x, 0.0f,  0.0f, 1.0f, 0.0f,

			 // Right face
			 half.x,  half.y, -half.z,  1.0f, 0.0f, 0.0f,  extents.z, extents.y,  1.0f, 0.0f, 0.0f,
			 half.x, half.y, half.z,  0.0f, 1.0f, 0.0f,    0.0f, extents.y,  1.0f, 0.0f, 0.0f,
			 half.x, -half.y, half.z,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 half.x, -half.y, -half.z,  1.0f, 1.0f, 0.0f,  extents.z, 0.0f,  1.0f, 0.0f, 0.0f,

			 // Left face
			 -half.x, half.y, half.z,  1.0f, 0.0f, 0.0f,  extents.z, extents.y,  -1.0f, 0.0f, 0.0f,
			 -half.x, half.y, -half.z,  0.0f, 1.0f, 0.0f, 0.0f, extents.y,  -1.0f, 0.0f, 0.0f,
			 -half.x, -half.y, -half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
			 -half.x, -half.y, half.z,  1.0f, 1.0f, 0.0f, extents.z, 0.0f,  -1.0f, 0.0f, 0.0f,

			 // Bottom face
			 half.x, -half.y, half.z,  1.0f, 0.0f, 0.0f,  extents.x, extents.z,  0.0f, -1.0f, 0.0f,
			 -half.x, -half.y, half.z,  0.0f, 1.0f, 0.0f, 0.0f, extents.z,  0.0f, -1.0f, 0.0f,
			 -half.x, -half.y, -half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
			 half.x, -half.y, -half.z,  1.0f, 1.0f, 0.0f, extents.x, 0.0f,  0.0f, -1.0f, 0.0f,

			 // Back face
			 -half.x, half.y, -half.z,  1.0f, 0.0f, 0.0f,  extents.x, extents.y,  0.0f, 0.0f, -1.0f,
			 half.x, half.y, -half.z,  0.0f, 1.0f, 0.0f,   0.0f, extents.y,  0.0f, 0.0f, -1.0f,
			 half.x, -half.y, -half.z, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
			 -half.x, -half.y, -half.z,  1.0f, 1.0f, 0.0f, extents.x, 0.0f,  0.0f, 0.0f, -1.0f,
		};

		std::vector<unsigned int> indicies =
		{
			// front face
			0, 1, 2,
			0, 2, 3,

			// top face
			4, 5, 6,
			4, 6, 7,

			// right face
			8, 9, 10,
			8, 10, 11,

			// left face
			12, 13, 14,
			12, 14, 15,

			// bottom face
			16, 17, 18,
			16, 18, 19,

			// back face
			20, 21, 22,
			20, 22, 23
		};

		eng::VertexLayout vertexLayout;

		// Position
		vertexLayout.elements.push_back({
			VertexElement::PositionIndex,
			3,
			GL_FLOAT,
			0 // index, size, type, offset
		});
		// Color
		vertexLayout.elements.push_back({
			VertexElement::ColorIndex,
			3,
			GL_FLOAT,
			sizeof(float) * 3 // index, size, type, offset
		});
		// UV
		vertexLayout.elements.push_back({
			VertexElement::UVIndex,
			2,
			GL_FLOAT,
			sizeof(float) * 6 // index, size, type, offset
		});
		// Normal
		vertexLayout.elements.push_back({
			VertexElement::NormalIndex,
			3,
			GL_FLOAT,
			sizeof(float) * 8 // index, size, type, offset
		});

		// Stride
		vertexLayout.stride = sizeof(float) * 11; // 3 position + 3 color + 2 uv + 3 normal

		// Create mesh 
		auto result = std::make_shared<eng::Mesh>(
			vertexLayout,
			verticies,
			indicies
		);

		return result;
	}

	/// <summary>
	/// Creates a UV sphere mesh with the specified radius, number of sectors (longitude) and stacks (latitude)
	/// </summary>
	/// <param name="radius"></param>
	/// <param name="sectors"></param>
	/// <param name="stacks"></param>
	/// <returns></returns>
	shared<Mesh> Mesh::CreateSphere(float radius, int sectors, int stacks)
	{
		constexpr float PI = 3.14159265358979323846f;

		List<float> verticies((stacks + 1) * (sectors + 1) * 8);
		for (int i = 0; i <= stacks; ++i)
		{
			float stackAngle = PI / 2.0f - static_cast<float>(i) * (PI / static_cast<float>(stacks)); // From -pi/2 to pi/2
			float xy = radius * cosf(stackAngle);// x-y plane radius at current stack
			float z = radius * sinf(stackAngle); // z value at current stack

			for (int j = 0; j <= sectors; ++j)
			{
				float sectorAngle = static_cast<float>(j) * (2.0f * PI / static_cast<float>(sectors)); // from 0 to 2pi

				// calculate vertex position
				float x = xy * cosf(sectorAngle);
				float y = xy * sinf(sectorAngle);

				size_t vertexStart = (i * (sectors + 1) + j) * 8; // 8 floats per vertex (position, color, uv, normal)

				// position
				verticies[vertexStart] = x;
				verticies[vertexStart + 1] = y;
				verticies[vertexStart + 2] = z;

				// normal (normalized position vector)
				float length = sqrtf(x * x + y * y + z * z);
				verticies[vertexStart + 3] = x / length; // normal x
				verticies[vertexStart + 4] = y / length; // normal y
				verticies[vertexStart + 5] = z / length; // normal z

				// uv coordinates
				verticies[vertexStart + 6] = static_cast<float>(j) / static_cast<float>(sectors); // u
				verticies[vertexStart + 7] = static_cast<float>(i) / static_cast<float>(stacks); // v
			}
		}
		
		// generate indicies
		List<unsigned int> indicies;
		for (int i = 0; i < stacks; ++i)
		{
			int k1 = i * (sectors + 1); // beginning of current stack
			int k2 = k1 + sectors + 1; // beginning of next stack

			for (int j = 0; j < sectors; ++j, ++k1, ++k2)
			{
				if (i != 0)
				{
					// first triangle
					indicies.push_back(k1);
					indicies.push_back(k2);
					indicies.push_back(k1 + 1);
				}

				if (i != (stacks - 1))
				{
					// second triangle
					indicies.push_back(k1 + 1);
					indicies.push_back(k2);
					indicies.push_back(k2 + 1);
				}
			}
		}

		eng::VertexLayout vertexLayout;
		
		// Position
		vertexLayout.elements.push_back({
			VertexElement::PositionIndex,
			3,
			GL_FLOAT,
			0 // index, size, type, offset
		});

		// Normal
		vertexLayout.elements.push_back({
			VertexElement::NormalIndex,
			3,
			GL_FLOAT,
			sizeof(float) * 3 // index, size, type, offset
		});

		// UV
		vertexLayout.elements.push_back({
			VertexElement::UVIndex,
			2,
			GL_FLOAT,
			sizeof(float) * 6 // index, size, type, offset
		});

		vertexLayout.stride = sizeof(float) * 8; // 3 position + 3 normal + 2 uv'

		auto result = std::make_shared<eng::Mesh>(
			vertexLayout,
			verticies,
			indicies
		);

		return result;
	}

	/// <summary>
	/// Creates a simple plane mesh in the X-Y plane with UV coordinates
	/// The plane is defined by four vertices forming a square, and two triangles are created to render the plane
	/// </summary>
	/// <returns></returns>
	shared<Mesh> Mesh::CreatePlane()
	{
		List<float> verticies =
		{
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f
		};

		List<uint32_t> indicies = 
		{
			0, 1, 2,
			0, 2, 3
		};

		eng::VertexLayout vertexLayout;

		// position
		vertexLayout.elements.push_back({
			VertexElement::PositionIndex,
			2,
			GL_FLOAT,
			0 // index, size, type, offset
		});
		vertexLayout.stride = sizeof(float) * 2; // 2 floats per vertex (position)

		auto result = std::make_shared<eng::Mesh>(
			vertexLayout,
			verticies,
			indicies
		);

		return result;
	}

	/// <summary>
	/// Creates a cylinder centered at the origin
	/// The cylinder is aligned along the Y axis and consists of:
	///     - Side wall vertices
	///     - Top cap vertices
	///     - Bottom cap vertices
	///
	/// Separate vertices are generated for caps and side walls so that
	/// normals are not shared between surfaces. This produces proper
	/// hard edges and correct lighting
	/// </summary>
	/// <param name="radius">Cylinder radius</param>
	/// <param name="height">Cylinder height</param>
	/// <param name="segments">Number of radial subdivisions</param>
	/// <returns>Generated cylinder mesh</returns>
	shared<Mesh> Mesh::CreateCylinder(float radius, float height, int segments)
	{
		constexpr float PI = 3.14159265358979323846f;

		List<float> vertices;
		List<uint32_t> indices;

		const float halfHeight = height * 0.5f;

		// Helper for inserting Position + Normal + UV vertices
		auto AddVertex =
			[&vertices](const glm::vec3& position,
				const glm::vec3& normal,
				const glm::vec2& uv)
			{
				vertices.push_back(position.x);
				vertices.push_back(position.y);
				vertices.push_back(position.z);

				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);

				vertices.push_back(uv.x);
				vertices.push_back(uv.y);
			};

		// SIDE WALL
		const uint32_t sideStartIndex = 0;

		for (int i = 0; i <= segments; ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(segments);
			float angle = t * 2.0f * PI;

			float x = cosf(angle) * radius;
			float z = sinf(angle) * radius;

			glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));

			// Top vertex
			AddVertex(
				glm::vec3(x, halfHeight, z),
				normal,
				glm::vec2(t, 1.0f)
			);

			// Bottom vertex
			AddVertex(
				glm::vec3(x, -halfHeight, z),
				normal,
				glm::vec2(t, 0.0f)
			);
		}

		// Generate side wall triangles
		for (int i = 0; i < segments; ++i)
		{
			uint32_t topLeft = sideStartIndex + i * 2;
			uint32_t bottomLeft = topLeft + 1;

			uint32_t topRight = topLeft + 2;
			uint32_t bottomRight = topLeft + 3;

			// First triangle
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);

			// Second triangle
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}

		// TOP CAP
		const uint32_t topCenterIndex =
			static_cast<uint32_t>(vertices.size() / 8);

		// Center vertex
		AddVertex(
			glm::vec3(0.0f, halfHeight, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec2(0.5f, 0.5f));

		const uint32_t topRingStart =
			static_cast<uint32_t>(vertices.size() / 8);

		for (int i = 0; i <= segments; ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(segments);
			float angle = t * 2.0f * PI;

			float x = cosf(angle) * radius;
			float z = sinf(angle) * radius;

			// Map circle coordinates into UV space
			float u = (x / radius + 1.0f) * 0.5f;
			float v = (z / radius + 1.0f) * 0.5f;

			AddVertex(
				glm::vec3(x, halfHeight, z),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec2(u, v)
			);
		}

		// Generate top cap triangles
		for (int i = 0; i < segments; ++i)
		{
			indices.push_back(topCenterIndex);
			indices.push_back(topRingStart + i + 1);
			indices.push_back(topRingStart + i);
		}

		// BOTTOM CAP
		const uint32_t bottomCenterIndex =
			static_cast<uint32_t>(vertices.size() / 8);

		AddVertex(
			glm::vec3(0.0f, -halfHeight, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec2(0.5f, 0.5f)
		);

		const uint32_t bottomRingStart =
			static_cast<uint32_t>(vertices.size() / 8);

		for (int i = 0; i <= segments; ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(segments);
			float angle = t * 2.0f * PI;

			float x = cosf(angle) * radius;
			float z = sinf(angle) * radius;

			float u = (x / radius + 1.0f) * 0.5f;
			float v = (z / radius + 1.0f) * 0.5f;

			AddVertex(
				glm::vec3(x, -halfHeight, z),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec2(u, v)
			);
		}

		// Generate bottom cap triangles
		for (int i = 0; i < segments; ++i)
		{
			indices.push_back(bottomCenterIndex);
			indices.push_back(bottomRingStart + i);
			indices.push_back(bottomRingStart + i + 1);
		}

		// Vertex Layout
		eng::VertexLayout vertexLayout;

		// Position
		vertexLayout.elements.push_back({
			VertexElement::PositionIndex,
			3,
			GL_FLOAT,
			0
		});

		// Normal
		vertexLayout.elements.push_back({
			VertexElement::NormalIndex,
			3,
			GL_FLOAT,
			sizeof(float) * 3
		});

		// UV
		vertexLayout.elements.push_back({
			VertexElement::UVIndex,
			2,
			GL_FLOAT,
			sizeof(float) * 6
		});

		vertexLayout.stride = sizeof(float) * 8;

		// Create Mesh
		auto result = std::make_shared<eng::Mesh>(
			vertexLayout,
			vertices,
			indices);

		return result;
	}

	/// <summary>
	/// Creates a cone centered at the origin.
	/// The cone is aligned along the Y axis and consists of:
	///     - Side wall vertices
	///     - Bottom cap vertices
	///
	/// Separate vertices are generated for the side and bottom cap so
	/// normals are not shared between surfaces. This produces proper
	/// hard edges and correct lighting
	///
	/// The cone's apex is located at +height/2 and the base is located
	/// at -height/2
	/// </summary>
	/// <param name="radius">Cone base radius</param>
	/// <param name="height">Cone height</param>
	/// <param name="segments">Number of radial subdivisions</param>
	/// <returns>Generated cone mesh</returns>
	shared<Mesh> Mesh::CreateCone(float radius, float height, int segments)
	{
		constexpr float PI = 3.14159265358979323846f;

		List<float> vertices;
		List<uint32_t> indices;

		const float halfHeight = height * 0.5f;

		// Helper for inserting Position + Normal + UV vertices
		auto AddVertex =
			[&vertices](const glm::vec3& position,
				const glm::vec3& normal,
				const glm::vec2& uv)
			{
				vertices.push_back(position.x);
				vertices.push_back(position.y);
				vertices.push_back(position.z);

				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);

				vertices.push_back(uv.x);
				vertices.push_back(uv.y);
			};

		// SIDE SURFACE
		const uint32_t sideApexIndex = 0;


		// Apex vertex for side surface.
		// Note:
		// We duplicate the apex specifically for the side surface so it is
		// not shared with the bottom cap geometry
		AddVertex(
			glm::vec3(0.0f, halfHeight, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec2(0.5f, 1.0f));

		const uint32_t sideRingStart =
			static_cast<uint32_t>(vertices.size() / 8);

		// Generate side ring vertices
		// We generate an extra vertex at the seam (segments + 1) so UVs
		// wrap correctly
		for (int i = 0; i <= segments; ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(segments);
			float angle = t * 2.0f * PI;

			float x = cosf(angle) * radius;
			float z = sinf(angle) * radius;

			// Side normal calculation
			// For a cone, normals are not purely radial
			// We incorporate the cone slope so lighting behaves correctly
			float slope = radius / height;

			glm::vec3 normal =
				glm::normalize(glm::vec3(
					x,
					slope * radius,
					z));

			AddVertex(
				glm::vec3(x, -halfHeight, z),
				normal,
				glm::vec2(t, 0.0f));
		}

		// Generate side triangles
		for (int i = 0; i < segments; ++i)
		{
			indices.push_back(sideApexIndex);
			indices.push_back(sideRingStart + i);
			indices.push_back(sideRingStart + i + 1);
		}

		// BOTTOM CAP
		const uint32_t bottomCenterIndex =
			static_cast<uint32_t>(vertices.size() / 8);

		AddVertex(
			glm::vec3(0.0f, -halfHeight, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec2(0.5f, 0.5f));

		const uint32_t bottomRingStart =
			static_cast<uint32_t>(vertices.size() / 8);

		// Generate bottom cap ring vertices
		// These vertices are duplicated from the side ring because they use
		// different normals
		for (int i = 0; i <= segments; ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(segments);
			float angle = t * 2.0f * PI;

			float x = cosf(angle) * radius;
			float z = sinf(angle) * radius;

			float u = (x / radius + 1.0f) * 0.5f;
			float v = (z / radius + 1.0f) * 0.5f;

			AddVertex(
				glm::vec3(x, -halfHeight, z),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec2(u, v));
		}

		// Generate bottom cap triangles
		for (int i = 0; i < segments; ++i)
		{
			indices.push_back(bottomCenterIndex);
			indices.push_back(bottomRingStart + i);
			indices.push_back(bottomRingStart + i + 1);
		}

		// Vertex Layout
		eng::VertexLayout vertexLayout;

		// Position
		vertexLayout.elements.push_back({
			VertexElement::PositionIndex,
			3,
			GL_FLOAT,
			0
		});

		// Normal
		vertexLayout.elements.push_back({
			VertexElement::NormalIndex,
			3,
			GL_FLOAT,
			sizeof(float) * 3
		});

		// UV
		vertexLayout.elements.push_back({
			VertexElement::UVIndex,
			2,
			GL_FLOAT,
			sizeof(float) * 6
		});

		vertexLayout.stride = sizeof(float) * 8;

		// Create Mesh
		auto result = std::make_shared<eng::Mesh>(
			vertexLayout,
			vertices,
			indices);

		return result;
	}

	// deprecated for now
#if 0
	shared<Mesh> Mesh::Load(const std::string& path)
	{
		auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);

		if (contents.empty()) return nullptr;

		auto readFloats = [](const cgltf_accessor* acc, cgltf_size i, float* out, int n)
			{
				std::fill(out, out + n, 0.0f);
				return cgltf_accessor_read_float(acc, i, out, n) == 1;
			};

		auto readIndex = [](const cgltf_accessor* acc, cgltf_size i)
			{
				cgltf_uint out = 0;
				cgltf_bool ok = cgltf_accessor_read_uint(acc, i, &out, 1);
				return ok ? static_cast<uint32_t>(out) : 0;
			};

		cgltf_options options = {};
		cgltf_data* data = nullptr;

		cgltf_result res = cgltf_parse(&options, contents.data(), contents.size(), &data);

		if (res != cgltf_result_success) return nullptr;

		auto fullPath = Engine::GetInstance().GetFileSystem().GetAssetsFolder() / path;
		// need to find and load the .bin buffer

		// load binary buffer
		// and convert the folder string().c_str()
		res = cgltf_load_buffers(&options, data, fullPath.remove_filename().string().c_str());
	
		if (res != cgltf_result_success)
		{
			cgltf_free(data);
			return nullptr;
		}

		shared<Mesh> result = nullptr;

		for (cgltf_size mi = 0; mi < data->meshes_count; ++mi)
		{
			auto& mesh = data->meshes[mi];
			for (cgltf_size pi = 0; pi < mesh.primitives_count; ++pi)
			{
				auto& primitive = mesh.primitives[pi];
				if (primitive.type != cgltf_primitive_type_triangles)
				{
					continue;
				}

				VertexLayout vertexLayout;
				cgltf_accessor* accessors[4] = { nullptr, nullptr, nullptr };

				for (cgltf_size ai = 0; ai < primitive.attributes_count; ++ai)
				{
					auto& attr = primitive.attributes[ai];
					auto acc = attr.data;
					if (!acc)
					{
						continue;
					}

					VertexElement element;
					element.type = GL_FLOAT;

					switch (attr.type)
					{
						case cgltf_attribute_type_position:
						{
							accessors[VertexElement::PositionIndex] = acc;
							element.index = VertexElement::PositionIndex;
							element.size = 3;
						}
							break;
						case cgltf_attribute_type_color:
						{
							// we only use COLOR_0 (attr.index == 0)
							if (attr.index != 0) continue;
							accessors[VertexElement::ColorIndex] = acc;
							element.index = VertexElement::ColorIndex;
							element.size = 3;
						}
							break;
						case cgltf_attribute_type_texcoord:
						{
							// we only use first index (attr.index == 0)
							if (attr.index != 0) continue;
							accessors[VertexElement::UVIndex] = acc;
							element.index = VertexElement::UVIndex;
							element.size = 2;
						}
							break;
						case cgltf_attribute_type_normal:
						{
							accessors[VertexElement::NormalIndex] = acc;
							element.index = VertexElement::NormalIndex;
							element.size = 3;
						}
							break;
						default:
							continue;
					}

					if (element.size > 0)
					{
						element.offset = vertexLayout.stride;
						vertexLayout.stride += element.size * sizeof(float);
						vertexLayout.elements.push_back(element);
					}
				}

				// allocate the buffer

				if (!accessors[VertexElement::PositionIndex]) continue;

				auto vertexCount = accessors[VertexElement::PositionIndex]->count;

				List<float> verticies;
				verticies.resize((vertexLayout.stride / sizeof(float)) * vertexCount);

				for (cgltf_size vi = 0; vi < vertexCount; ++vi)
				{
					for (auto& el : vertexLayout.elements)
					{
						if (!accessors[el.index]) continue;

						auto index = (vi * vertexLayout.stride + el.offset) / sizeof(float);
						float* outData = &verticies[index];
						readFloats(accessors[el.index], vi, outData, el.size); // reads attribute for vertex vi
					}
				}

				if (primitive.indices)
				{
					auto indexCount = primitive.indices->count;
					List<uint32_t> indicies(indexCount);
					for (cgltf_size i = 0; i < indexCount; ++i)
					{
						indicies[i] = readIndex(primitive.indices, i);
					}
					result = std::make_shared<Mesh>(vertexLayout, verticies, indicies);
				}
				else
				{
					result = std::make_shared<Mesh>(vertexLayout, verticies);
				}

				if (result) break;
			}

			if (result) break;
		}

		cgltf_free(data);

		return result;
	}
#endif
}
