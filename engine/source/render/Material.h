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
	class Texture;

	class Material
	{
	public:
		ShaderProgram* GetShaderProgram() noexcept;
		void SetShaderProgram(const shared<ShaderProgram>& shaderProgram) noexcept;
		void SetFloatParam(const std::string& name, float value) noexcept;
		void SetFloatParam(const std::string& name, float v0, float v1) noexcept;
		void SetTextureParam(const std::string& name, const shared<Texture>& texture);

		void Bind();

		static shared<Material> Load(const std::string& path);

	private:
		shared<ShaderProgram> m_ShaderProgram;
		Dictionary<std::string, float> m_FloatParams;
		Dictionary<std::string, std::pair<float, float>> m_Float2Params;
		Dictionary<std::string, shared<Texture>> m_Textures;
	};
}

#endif // MATERIAL_H
