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
	eng::Material m_Material;
	std::unique_ptr<eng::Mesh> m_Mesh;
};

#endif // GAME_H

// In summary
// Shader Program defines how pixels are rendered using shaders.
// Material stores the shader and uniform values
// Mesh holds the geometry data (vertices, indices) for rendering.
// The GraphicsAPI provides unified access to create and manage these resources.
