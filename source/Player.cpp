#include "Player.h"
#include "Bullet.h"

#include <GLFW/glfw3.h>

void Player::Init()
{
// using scene.sc to load Player properties
#if 0
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
#endif

	if (auto bullet = FindChildByName("bullet_33"))
	{
		bullet->SetActive(false);
	}

	if (auto fire = FindChildByName("BOOM_35"))
	{
		fire->SetActive(false);
	}

	if (auto gun = FindChildByName("Gun"))
	{
		m_AnimationComponent = gun->GetComponent<eng::AnimationComponent>();
	}

	m_AudioComponent = GetComponent<eng::AudioComponent>();
	m_PlayerControllerComponent = GetComponent<eng::PlayerControllerComponent>();
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

			// if the shoot sound is already playing, stop it and play it again to prevent spamming the sound when shooting rapidly
			if (m_AudioComponent)
			{
				if (m_AudioComponent->IsPlaying("shoot"))
				{
					m_AudioComponent->Stop("shoot");
				}
				m_AudioComponent->Play("shoot");
			}

			// create a bullet and set its position and direction based on the gun's position and forward direction
			auto bullet = m_Scene->CreateGameObject<Bullet>("Bullet");
			auto bulletMaterial = eng::Material::Load("materials/suzanne.mat");
			float bulletRadius = 0.2f;
			auto bulletMesh = eng::Mesh::CreateSphere(bulletRadius, 32, 32);
			bullet->AddComponenet(new eng::MeshComponent(bulletMaterial, bulletMesh));

			glm::vec3 pos = glm::vec3(0.0f);
			if (auto child = FindChildByName("BOOM_35"))
			{
				pos = child->GetWorldPosition();
			}
			bullet->SetPosition(pos + m_Rotation * glm::vec3(-0.2f, 0.2f, -1.75f));

			auto bulletCollider = std::make_shared<eng::SphereCollider>(bulletRadius);
			auto bulletRigidBody = std::make_shared<eng::RigidBody>(
				eng::BodyType::Dynamic,
				bulletCollider,
				10.0f, // mass
				0.1f // friction
			);
			bullet->AddComponenet(new eng::PhysicsComponent(bulletRigidBody));

			glm::vec3 front = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
			bulletRigidBody->ApplyImpulse(front * 500.0f);
		}
	}
	
	// play jump sound when space is pressed, but only if it's not already playing to prevent spamming the sound
	if (input.IsKeyPressed(GLFW_KEY_SPACE) && m_PlayerControllerComponent && m_PlayerControllerComponent->IsOnGround())
	{
		if (m_AudioComponent && !m_AudioComponent->IsPlaying("jump"))
		{
			m_AudioComponent->Play("jump");
		}
	}
	//else
	//{
	//	if (m_AudioComponent && m_AudioComponent->IsPlaying("jump"))
	//	{
	//		m_AudioComponent->Stop("jump");
	//	}
	//}

	bool walking = input.IsKeyPressed(GLFW_KEY_W) ||
				   input.IsKeyPressed(GLFW_KEY_A) || 
				   input.IsKeyPressed(GLFW_KEY_S) || 
				   input.IsKeyPressed(GLFW_KEY_D);

	// play footstep sound if the player is walking and on the ground, otherwise stop it
	if (walking && m_PlayerControllerComponent && m_PlayerControllerComponent->IsOnGround())
	{
		if (m_AudioComponent && !m_AudioComponent->IsPlaying("step"))
		{
			m_AudioComponent->Play("step", true);
		}
	}
	else
	{
		if (m_AudioComponent && m_AudioComponent->IsPlaying("step"))
		{
			m_AudioComponent->Stop("step");
		}
	}
}
