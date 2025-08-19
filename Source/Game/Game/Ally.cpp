#include "../GamePCH.h"
#include "Ally.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "Renderer/ParticleSystem.h"
#include "Engine.h"
#include "Core/Random.h"

FACTORY_REGISTER(Ally)

void Ally::Update(float deltaTime)
{
//	bool enemySeen = false;
//	Enemy* enemy = m_scene->GetActorByName<Enemy>("enemy");
//
//	if (enemy) {
//		bool playerSeen = false;
//
//		Enemy* enemy = m_scene->GetActorByName<Enemy>("enemy");
//		if (enemy) {
//			claw::vec2 direction{ 0, 0 };
//			direction = enemy->m_transform.position - m_transform.position;
//
//			direction = direction.Normalize();
//			claw::vec2 forward = claw::vec2{ 1, 0 }.Rotate(claw::Math::degToRad(m_transform.rotation));
//
//			float angle = claw::Math::radToDeg(claw::vec2::AngleBetween(forward, direction));
//			enemySeen = angle <= 45; // angle threshold for enemy detection
//
//			if (enemySeen) {
//				float angle = claw::vec2::SignedAngleBetween(forward, direction);
//				angle = claw::Math::Sign(angle);
//				m_transform.rotation += claw::Math::radToDeg(angle * 5 * deltaTime);
//			}
//		}
//	}
//
//
//	claw::vec2 force = claw::vec2{ 1,0 }.Rotate(claw::Math::degToRad(m_transform.rotation)) * speed;
//	//velocity += force;
//
//	auto* rb = GetComponent<claw::RigidBody>();
//	if (rb) {
//		rb->velocity += force;
//	}
//
//	if (speed > 0) {
//		claw::Particle particle;
//		particle.position = m_transform.position;
//		particle.color = claw::vec3{ 0,0.75f,0 };
//		particle.velocity = claw::vec2{ claw::Random::onUnitCircle() * claw::Random::getReal(20.0f, 40.0f) };
//		particle.lifeSpan = claw::Random::getReal(0.25f, 0.5f);
//		claw::GetEngine().GetParticleSystem().AddParticle(particle);
//
//	}
//
//	m_transform.position.x = claw::Math::Wrap(m_transform.position.x, 0.0f, (float)claw::GetEngine().GetRenderer().getWidth());
//	m_transform.position.y = claw::Math::Wrap(m_transform.position.y, 0.0f, (float)claw::GetEngine().GetRenderer().getHeight());
//
//	Actor::Update(deltaTime);
}

void Ally::onCollision(claw::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		claw::GetEngine().GetAudio().playSound("death");
		for (int i = 0; i < 100; i++) {
			claw::Particle particle;
			particle.position = owner->m_transform.position;
			particle.color = claw::vec3{ 1,1,1 };
			particle.velocity = claw::vec2{ claw::Random::onUnitCircle() * claw::Random::getReal(10.0f, 200.0f) };
			particle.lifeSpan = 2.0f;
			claw::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
