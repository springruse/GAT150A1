#include "../GamePCH.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float deltaTime)
{
//	bool playerSeen = false;
//	Actor* player = owner->m_scene->GetActorByName<Actor>("player");
//
//	if (player) {
//		bool playerSeen = false;
//
//		Player* player = owner->m_scene->GetActorByName<Player>("player");
//		if (player) {
//			claw::vec2 direction{ 0, 0 };
//			direction = player->owner->m_transform.position - owner->m_transform.position;
//
//			direction = direction.Normalize();
//			claw::vec2 forward = claw::vec2{ 1, 0 }.Rotate(claw::Math::degToRad(owner->m_transform.rotation));
//
//			float angle = claw::Math::radToDeg(claw::vec2::AngleBetween(forward, direction));
//			playerSeen = angle <= 45; // angle threshold for player detection
//
//			if (playerSeen) {
//				float angle = claw::vec2::SignedAngleBetween(forward, direction);
//				angle = claw::Math::Sign(angle);
//				owner->m_transform.rotation += claw::Math::radToDeg(angle * 5 * owner->deltaTime);
//			}
//		}
//	}
//
//	claw::vec2 force = claw::vec2{ 1,0 }.Rotate(claw::Math::degToRad(owner->m_transform.rotation)) * owner->speed;
//	//velocity += force; * dt;
//	auto* rb = owner->GetComponent<claw::RigidBody>();
//	if (rb) {
//		rb->velocity += force;
//	}
//
//	owner->m_transform.position.x = claw::Math::Wrap(owner->m_transform.position.x, 0.0f, (float)claw::GetEngine().GetRenderer().getWidth());
//	owner->m_transform.position.y = claw::Math::Wrap(owner->m_transform.position.y, 0.0f, (float)claw::GetEngine().GetRenderer().getHeight());
//
//	owner->firetimer = owner->deltaTime;
//
//	if (owner->firetimer <= 0 && playerSeen)
//	{
//		firetimer = fireTime;
//		auto rocketModel = claw::Resources().Get<claw::Texture>("texture/redShip.png", claw::GetEngine().GetRenderer());
//		claw::Transform rocketTransform{ this->m_transform.position, this->m_transform.rotation, 1.0f };
//		auto rocket = std::make_unique<Rocket>(rocketTransform); // , rocketModel);
//		rocket->speed = 30.0f;
//		rocket->lifeSpan = 1.5f;
//		rocket->name = "rocket";
//		rocket->tag = "enemy"; 
//
//		//components
//		auto spriteRenderer = std::make_unique<claw::SpriteRenderer>();
//		spriteRenderer->textureName = "texture/redShip.png"; // rocket texture
//		rocket->AddComponent(std::move(spriteRenderer));
//
//		auto rb = std::make_unique<claw::RigidBody>();
//		rocket->AddComponent(std::move(rb));
//
//		auto collider = std::make_unique<claw::CircleCollider2D>();
//		collider->radius = 10.0f;
//		rocket->AddComponent(std::move(collider));
//
//		m_scene->AddActor(std::move(rocket));
//	}
//
//	Actor::Update(deltaTime);
//
}

void Enemy::onCollision(claw::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true; 
		claw::GetEngine().GetAudio().playSound("death");
		owner->m_scene->GetGame()->addPoints(100); // Add points for destroying the enemy
		for (int i = 0; i < 100; i++) {
			claw::Particle particle;
			particle.position = owner->m_transform.position;
			particle.color = claw::vec3{ 1,1,1 };
			particle.velocity = claw::vec2{claw::Random::onUnitCircle() * claw::Random::getReal(10.0f, 200.0f)};
			particle.lifeSpan = 2.0f;
			claw::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
