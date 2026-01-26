#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <unordered_map>
#include <string>

namespace eng
{
	class ShaderProgram;

	class Material
	{
	public:
		void SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) noexcept;
		void SetFloatParam(const std::string& name, float value) noexcept;

		void Bind();

	private:
		std::shared_ptr<ShaderProgram> m_ShaderProgram;
		std::unordered_map<std::string, float> m_FloatParams;
	};
}

#endif // MATERIAL_H
