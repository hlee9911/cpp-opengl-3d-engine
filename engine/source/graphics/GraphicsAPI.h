#pragma once

#include <GL/glew.h>

#include <memory>
#include <vector>
#include <string>

#include "Core.h"

namespace eng
{
	class ShaderProgram;
	class Material;
	class Mesh;

	// Blend modes for rendering
	enum class BlendMode
	{
		Disabled,
		Alpha,
		Additive,
		Multiply
	};

	struct Rect
	{
		int x = 0;
		int y = 0;

		int width = 0;
		int height = 0;
	};

	// Used as a key for caching shader programs based on their vertex and fragment source code
	struct ShaderKey
	{
		std::string vertexSource;
		std::string fragmentSource;

		bool operator==(const ShaderKey& other) const
		{
			return vertexSource == other.vertexSource &&
				fragmentSource == other.fragmentSource;
		}
	};

	// Custom hash function for ShaderKey to be used in unordered_map(Dictionary)
	struct ShaderKeyHash
	{
		std::size_t operator()(const ShaderKey& key) const
		{
			size_t h1 = std::hash<std::string>{}(key.vertexSource);
			size_t h2 = std::hash<std::string>{}(key.fragmentSource);
			return h1 ^ (h2 << 1); // Combine the two hashes
		}
	};

	class GraphicsAPI
	{
	public:
		bool Init();
		shared<ShaderProgram> CreateShaderProgram(
			const std::string& vertexSource, 
			const std::string& fragmentSource);

		const shared<ShaderProgram>& GetDefaultShaderProgram();
		const shared<ShaderProgram>& GetDefault2DShaderProgram();
		const shared<ShaderProgram>& GetDefaultUIShaderProgram();

		GLuint CreateVertexBuffer(const std::vector<float>& verticies);
		GLuint CreateIndexBuffer(const std::vector<uint32_t>& indicies);

		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();
		const Rect& GetViewport() const;
		void SetViewport(int x, int y, int width, int height);
		void SetDepthTestEnabled(bool enabled);
		void SetBlendMode(BlendMode mode);
	
		void BindShaderProgram(ShaderProgram* shaderProgram);
		void BindMaterial(Material* material);
		void BindMesh(Mesh* mesh);
		void UnbindMesh(Mesh* mesh);
		void DrawMesh(Mesh* mesh);

	private:
		Rect m_Viewport;
		shared<ShaderProgram> m_DefaultShaderProgram;
		shared<ShaderProgram> m_Default2DShaderProgram;
		shared<ShaderProgram> m_DefaultUIShaderProgram;
		Dictionary<ShaderKey, shared<ShaderProgram>, ShaderKeyHash> m_ShaderCache;
	};
}
