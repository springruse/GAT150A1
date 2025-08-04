#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "EngineGame/Scene.h"
#include "Renderer/Renderer.h"
#include <EngineGame/Game.h>
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Rocket.h"
#include "Math/Vector3.h"
#include "GameData.h"

void Enemy::Update(float deltaTime)
{
	bool playerSeen = false;
	Player* player = m_scene->GetActorByName<Player>("player");

	if (player) {
		bool playerSeen = false;

		Player* player = m_scene->GetActorByName<Player>("player");
		if (player) {
			piMath::vec2 direction{ 0, 0 };
			direction = player->m_transform.position - m_transform.position;

			direction = direction.Normalize();
			piMath::vec2 forward = piMath::vec2{ 1, 0 }.Rotate(piMath::Math::degToRad(m_transform.rotation));

			float angle = piMath::Math::radToDeg(piMath::vec2::AngleBetween(forward, direction));
			playerSeen = angle <= 30;

			if (playerSeen) {
				float angle = piMath::vec2::SignedAngleBetween(forward, direction);
				angle = piMath::Math::Sign(angle);
				m_transform.rotation += piMath::Math::radToDeg(angle * 5 * deltaTime);
			}
		}
	}

	piMath::vec2 force = piMath::vec2{ 1,0 }.Rotate(piMath::Math::degToRad(m_transform.rotation)) * speed;
	velocity += force;
		
	m_transform.position.x = piMath::Math::Wrap(m_transform.position.x, 0.0f, (float)piMath::GetEngine().GetRenderer().getWidth());
	m_transform.position.y = piMath::Math::Wrap(m_transform.position.y, 0.0f, (float)piMath::GetEngine().GetRenderer().getHeight());

	firetimer = deltaTime;

	if (firetimer <= 0 && playerSeen)
	{
		firetimer = fireTime;
		std::shared_ptr<piMath::Model> rocketModel = std::make_shared<piMath::Model>(GameData::rocketPoints, piMath::vec3{ 1,1,1 });
		piMath::Transform rocketTransform{ this->m_transform.position, this->m_transform.rotation, 1.0f };
		auto rocket = std::make_unique<Rocket>(rocketTransform, rocketModel);
		rocket->speed = 30.0f;
		rocket->lifeSpan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy"; 
		
		m_scene->AddActor(std::move(rocket));
	}

	Actor::Update(deltaTime);

}

void Enemy::onCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true; 
		piMath::GetEngine().GetAudio().playSound("death");
		m_scene->GetGame()->addPoints(100); // Add points to the game when an enemy is destroyed
		for (int i = 0; i < 100; i++) {
			piMath::Particle particle;
			particle.position = m_transform.position;
			particle.color = piMath::vec3{ 1,1,1 };
			particle.velocity = piMath::vec2{piMath::Random::onUnitCircle() * piMath::Random::getReal(10.0f, 200.0f)};
			particle.lifeSpan = 2.0f;
			piMath::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
