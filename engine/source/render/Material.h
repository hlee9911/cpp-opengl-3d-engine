#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <unordered_map>
#include <string>

#include "Core.h"

namespace eng
{
	class ShaderProgram;

	class Material
	{
	public:
		ShaderProgram* GetShaderProgram() noexcept;
		void SetShaderProgram(const shared<ShaderProgram>& shaderProgram) noexcept;
		void SetFloatParam(const std::string& name, float value) noexcept;
		void SetFloatParam(const std::string& name, float v0, float v1) noexcept;

		void Bind();


	private:
		shared<ShaderProgram> m_ShaderProgram;
		Dictionary<std::string, float> m_FloatParams;
		Dictionary<std::string, std::pair<float, float>> m_Float2Params;
	};
}

#endif // MATERIAL_H
