#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <glm/vec3.hpp>

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
		void SetFloatParam(const std::string& name, const glm::vec3& value) noexcept;
		void SetTextureParam(const std::string& name, const shared<Texture>& texture);
		void SetBoolParam(const std::string& name, bool value) noexcept;

		const glm::vec3& GetFloat3Params(const std::string& name) noexcept;

		void Bind();

		static shared<Material> Load(const std::string& path);

	private:
		shared<ShaderProgram> m_ShaderProgram;
		Dictionary<std::string, float> m_FloatParams;
		Dictionary<std::string, std::pair<float, float>> m_Float2Params;
		Dictionary<std::string, glm::vec3> m_Float3Params;
		Dictionary<std::string, shared<Texture>> m_Textures;
		Dictionary<std::string, bool> m_BoolParams;
	};
}
