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
		ShaderProgram* GetShaderProgram() noexcept;
		void SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) noexcept;
		void SetFloatParam(const std::string& name, float value) noexcept;
		void SetFloatParam(const std::string& name, float v0, float v1) noexcept;

		void Bind();


	private:
		std::shared_ptr<ShaderProgram> m_ShaderProgram;
		std::unordered_map<std::string, float> m_FloatParams;
		std::unordered_map<std::string, std::pair<float, float>> m_Float2Params;
	};
}

#endif // MATERIAL_H
