#pragma once
#ifndef GRAPHICSAPI_H
#define GRAPHICSAPI_H

#include <GL/glew.h>

#include <memory>
#include <string>

namespace eng
{
	class ShaderProgram;

	class GraphicsAPI
	{
	public:
		std::shared_ptr<ShaderProgram> CreateShaderProgram(
			const std::string& vertexSource, 
			const std::string& fragmentSource);
	
		void BindShaderProgram(ShaderProgram* shaderProgram);
	};
}

#endif // GRAPHICSAPI_H
