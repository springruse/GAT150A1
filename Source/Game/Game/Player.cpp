#include "../GamePCH.h"
#include "Player.h"
#include "Engine.h"
#include "GameData.h"
#include "Rocket.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{

	claw::vec2 direction{ 1,0 };

	float rotate = 0;

	// rotation speed
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_A))  rotate = -1;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_D))  rotate = +1;

	owner->m_transform.rotation += (rotate * rotationSpeed) * dt;

	//thrust speed
	float thrust = 0;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_W))  thrust = +1;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_S))  thrust = -1;
	// player bounds
	owner->m_transform.position.x = claw::Math::Wrap(owner->m_transform.position.x, 0.0f, (float)claw::GetEngine().GetRenderer().getWidth());
	owner->m_transform.position.y = claw::Math::Wrap(owner->m_transform.position.y, 0.0f, (float)claw::GetEngine().GetRenderer().getHeight());

	claw::vec2 force = direction.Rotate(claw::Math::degToRad(owner->m_transform.rotation)) * thrust * speed;
	//velocity += force;

	auto* rb = owner->GetComponent<claw::RigidBody>();
	if (rb) {
		rb->velocity += force;
	}

	if (force.Length() > 0) {
		claw::Particle particle;
		particle.position = owner->m_transform.position;
		particle.color = claw::vec3{ 1,1,1 };
		particle.velocity = claw::vec2{ claw::Random::onUnitCircle() * claw::Random::getReal(50.0f, 80.0f) };
		particle.lifeSpan = 1.0f;
		claw::GetEngine().GetParticleSystem().AddParticle(particle);

	}
}
	
	// check if player fires
	//fireTimer -= dt;
	//if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_E))
	//{
	//	fireTimer = fireTime; // Reset fire timer

	//	auto sound = claw::GetEngine().GetAudio().playSound(*claw::Resources().Get<claw::AudioClip>("shipBlast1.wav", claw::GetEngine().GetAudio()).get());
	//	/*if (sound) {
	//		piMath::GetEngine().GetAudio().playSound(&sound);
	//	};*/
	//	claw::Transform rocketTransform{ this->m_transform.position, this->m_transform.rotation, 1.0f };
	//	auto rocket = std::make_unique<Rocket>(rocketTransform); // , piMath::Resources().Get<piMath::Texture>("texture/blue_01.png", piMath::GetEngine().GetRenderer()));
	//	rocket->speed = 600.0f;
	//	rocket->lifeSpan = 1.5f;
	//	rocket->name = "rocket";
	//	rocket->tag = "player"; // Set rocket name for identification

//		//components
//		auto spriteRenderer = std::make_unique<claw::SpriteRenderer>();
//		spriteRenderer->textureName = "texture/missle.png"; // rocket texture
//		rocket->AddComponent(std::move(spriteRenderer));
//
//		auto rb = std::make_unique<claw::RigidBody>();
//		rocket->AddComponent(std::move(rb));
//
//		auto collider = std::make_unique<claw::CircleCollider2D>();
//		collider->radius = 10.0f;
//		rocket->AddComponent(std::move(collider));
//
//		owner->m_scene->AddActor(std::move(rocket));
//
//	}
//
//	claw::Actor::Update(dt);
//
//}


void Player::OnCollision(claw::Actor* other)
{

		if (owner->tag != other->tag) {
			owner->destroyed = true;
			EVENT_NOTIFY("playerDead");
			claw::EventManager::Instance().Notify(claw::Event{ "playerDead", true });
			claw::GetEngine().GetAudio().playSound("death");
			dynamic_cast<SpaceGame*>(owner->m_scene->GetGame())->OnPlayerDeath(); // Notify the game of player death
	}
}

void Player::Read(const claw::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, damping);
	JSON_READ(value, rotationSpeed);
	JSON_READ(value, fireTime);

}
