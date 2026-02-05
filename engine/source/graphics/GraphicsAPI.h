#pragma once
#ifndef GRAPHICSAPI_H
#define GRAPHICSAPI_H

#include <GL/glew.h>

#include <memory>
#include <vector>
#include <string>

namespace eng
{
	class ShaderProgram;
	class Material;
	class Mesh;

	class GraphicsAPI
	{
	public:
		bool Init();
		std::shared_ptr<ShaderProgram> CreateShaderProgram(
			const std::string& vertexSource, 
			const std::string& fragmentSource);

		GLuint CreateVertexBuffer(const std::vector<float>& verticies);
		GLuint CreateIndexBuffer(const std::vector<uint32_t>& indicies);

		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();
	
		void BindShaderProgram(ShaderProgram* shaderProgram);
		void BindMaterial(Material* material);
		void BindMesh(Mesh* mesh);
		void DrawMesh(Mesh* mesh);
	};
}

#endif // GRAPHICSAPI_H
