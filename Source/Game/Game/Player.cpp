#include "Player.h"
#include "Engine.h"
#include "GameData.h"
#include "Rocket.h"
#include "Renderer/Model.h"
#include "EngineGame/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "SpaceGame.h"
#include "Math/Transform.h"
#include "Renderer/ParticleSystem.h"
#include "Audio/AudioSystem.h"

#include "Core/Random.h"

void Player::Update(float dt)
{

	piMath::vec2 direction{ 1,0 };

    float rotate = 0;
	
	// rotation speed
    if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_A))  rotate =  -1; 
    if(piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_D))  rotate = +1; 

	m_transform.rotation += (rotate * rotationSpeed) * dt;

	//thrust speed
    float thrust = 0;
	if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_W))  thrust = +1;
	if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_S))  thrust = -1;
	// player bounds
	m_transform.position.x = piMath::Math::Wrap(m_transform.position.x, 0.0f, (float)piMath::GetEngine().GetRenderer().getWidth());
	m_transform.position.y = piMath::Math::Wrap(m_transform.position.y, 0.0f, (float)piMath::GetEngine().GetRenderer().getHeight());

	piMath::vec2 force = direction.Rotate(piMath::Math::degToRad(m_transform.rotation)) * thrust * speed;
	velocity += force;

	if (force.Length() > 0) {
		piMath::Particle particle;
		particle.position = m_transform.position;
		particle.color = piMath::vec3{ 1,1,1 };
		particle.velocity = piMath::vec2{ piMath::Random::onUnitCircle() * piMath::Random::getReal(50.0f, 80.0f) };
		particle.lifeSpan = 1.0f;
		piMath::GetEngine().GetParticleSystem().AddParticle(particle);

	}
	
	// check if player fires
	fireTimer -= dt;
	if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_E))
	{
		fireTimer = fireTime; // Reset fire timer
		piMath::GetEngine().GetAudio().playSound("blaster");
		std::shared_ptr<piMath::Model> rocketModel = std::make_shared<piMath::Model>(GameData::rocketPoints, piMath::vec3{ 1,1,1 });
		piMath::Transform rocketTransform{ this->m_transform.position, this->m_transform.rotation, 1.0f };
		auto rocket = std::make_unique<Rocket>(rocketTransform, rocketModel);
		rocket->speed = 60.0f;
		rocket->lifeSpan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "player"; // Set rocket name for identification
		m_scene->AddActor(std::move(rocket));
	}

	Actor::Update(dt);

}


void Player::onCollision(Actor* other)
{

	
	if (tag != other->tag) {
		destroyed = true;
		piMath::GetEngine().GetAudio().playSound("death");
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath(); // Notify the game of player death
	}
	std::cout << other->tag << std::endl;
	
}
