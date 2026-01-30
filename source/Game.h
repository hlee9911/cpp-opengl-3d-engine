#pragma once
#ifndef GAME_H
#define GAME_H

#include <eng.h>

#include <memory>

class Game : public eng::Application
{
public:
	bool Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

private:
	/*eng::Material m_Material;
	std::unique_ptr<eng::Mesh> m_Mesh;
	float m_OffsetX = 0.0f;
	float m_OffsetY = 0.0f;*/

	eng::Scene m_Scene;
};

#endif // GAME_H

// In summary
// Shader Program defines how pixels are rendered using shaders.
// Material stores the shader and uniform values
// Mesh holds the geometry data (vertices, indices) for rendering.
// The GraphicsAPI provides unified access to create and manage these resources.
