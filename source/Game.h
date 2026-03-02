#pragma once

#include <eng.h>

#include <memory>

#include "Core.h"

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

	eng::Scene* m_Scene = nullptr;
};

// In summary
// Shader Program defines how pixels are rendered using shaders.
// Material stores the shader and uniform values
// Mesh holds the geometry data (vertices, indices) for rendering.
// The GraphicsAPI provides unified access to create and manage these resources.

// Model transforms local space into world spce
// View transforms world spce into camera space (as if moving the world), view is inverse
// Projection transform camera space into the screen space // maps 3d to 2d

// Camera only renders only between the near and far planes
// forms view frustum
// Near Plane is the closest visible distance
// Far Plane is the farthest visible distance
// Aspect Ratio: Width / Height and affects horizontal scaling

// Z-buffer
// Invisible grayscale image, the sme size as your screen
// for every pixel you draw, it stores the depth, how far that pixel is from the camera
// when draawing the next object, the GPU compares its depth against whats already stored
// if its farther, it gets hidden
// with the depth testing, the GPU knows the sphere is behind and hides it correctly
// by default, in OpenGL, the z-buffer is disbled, so we need to enable it

// Quaternion
// A quaternion has four components: x, y, z, and w
// orientation is one value not three separate angles
// this avoids rotation-order issue entirely

// Lighting
// lightDir = normalize(lightPos - fragPos);
// float diffuseFactor = dot(normal, lightDir);

// Specular lighting
// Specular gives shiny reflections at certain angles, 
// it depends on the view direction as well as the light direction

