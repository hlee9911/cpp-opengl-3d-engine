#include "Player.h"

#include <GLFW/glfw3.h>

void Player::Init()
{
	// Create a camera and attach it to the player
	// auto camera = m_Scene->CreateGameObject("Camera");
	AddComponenet(new eng::CameraComponent());
	SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	AddComponenet(new eng::PlayerControllerComponent());

	// Load the gun model and attach it to the camera
	auto gun = eng::GameObject::LoadGLTF("models/sten_gunmachine_carbine/scene.gltf");
	gun->SetParent(this);
	gun->SetPosition(glm::vec3(0.75f, -0.5f, -0.75f));
	gun->SetScale(glm::vec3(-1.0f, 1.0f, 1.0f)); // scaling by -1 on the x axis to flip the model, since it's facing the wrong way

	if (auto anim = gun->GetComponent<eng::AnimationComponent>())
	{
		if (auto bullet = gun->FindChildByName("bullet_33"))
		{
			bullet->SetActive(false);
		}

		if (auto fire = gun->FindChildByName("BOOM_35"))
		{
			fire->SetActive(false);
		}

		anim->Play("shoot", false);
	}

	m_AnimationComponent = gun->GetComponent<eng::AnimationComponent>();
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	
	auto& input = eng::Engine::GetInstance().GetInputManager();
	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (m_AnimationComponent && !m_AnimationComponent->IsPlaying())
		{
			m_AnimationComponent->Play("shoot", false);
		}
	}
}
