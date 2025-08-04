#include "Ally.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "Renderer/ParticleSystem.h"
#include "Engine.h"
#include "Core/Random.h"
void Ally::Update(float deltaTime)
{
	bool enemySeen = false;
	Enemy* enemy = m_scene->GetActorByName<Enemy>("enemy");

	if (enemy) {
		bool playerSeen = false;

		Enemy* enemy = m_scene->GetActorByName<Enemy>("enemy");
		if (enemy) {
			piMath::vec2 direction{ 0, 0 };
			direction = enemy->m_transform.position - m_transform.position;

			direction = direction.Normalize();
			piMath::vec2 forward = piMath::vec2{ 1, 0 }.Rotate(piMath::Math::degToRad(m_transform.rotation));

			float angle = piMath::Math::radToDeg(piMath::vec2::AngleBetween(forward, direction));
			enemySeen = angle <= 30;

			if (enemySeen) {
				float angle = piMath::vec2::SignedAngleBetween(forward, direction);
				angle = piMath::Math::Sign(angle);
				m_transform.rotation += piMath::Math::radToDeg(angle * 5 * deltaTime);
			}
		}

	
	}


	piMath::vec2 force = piMath::vec2{ 1,0 }.Rotate(piMath::Math::degToRad(m_transform.rotation)) * speed;
	velocity += force;

	if (speed > 0) {
		piMath::Particle particle;
		particle.position = m_transform.position;
		particle.color = piMath::vec3{ 0,0.75f,0 };
		particle.velocity = piMath::vec2{ piMath::Random::onUnitCircle() * piMath::Random::getReal(20.0f, 40.0f) };
		particle.lifeSpan = piMath::Random::getReal(0.25f, 0.5f);
		piMath::GetEngine().GetParticleSystem().AddParticle(particle);

	}

	m_transform.position.x = piMath::Math::Wrap(m_transform.position.x, 0.0f, (float)piMath::GetEngine().GetRenderer().getWidth());
	m_transform.position.y = piMath::Math::Wrap(m_transform.position.y, 0.0f, (float)piMath::GetEngine().GetRenderer().getHeight());

	Actor::Update(deltaTime);
}

void Ally::onCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true;
		piMath::GetEngine().GetAudio().playSound("death");
		for (int i = 0; i < 100; i++) {
			piMath::Particle particle;
			particle.position = m_transform.position;
			particle.color = piMath::vec3{ 1,1,1 };
			particle.velocity = piMath::vec2{ piMath::Random::onUnitCircle() * piMath::Random::getReal(10.0f, 200.0f) };
			particle.lifeSpan = 2.0f;
			piMath::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
