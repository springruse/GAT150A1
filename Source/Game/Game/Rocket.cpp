#include "Rocket.h"
#include "EngineGame/Actor.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"
#include <vector>
//unfinished but is similar to enemy.cpp

void Rocket::Update(float deltaTime)
{
	piMath::vec2 force = piMath::vec2{ 1,0 }.Rotate(piMath::Math::degToRad(m_transform.rotation)) * speed;
	velocity += force;

	float angle = m_transform.rotation + piMath::Random::getReal(-30.0f, 30.0f);
	piMath::vec2 velocity = piMath::vec2{ 1,0 }.Rotate(piMath::Math::degToRad(angle));
	velocity += piMath::Random::getReal(100.0f, 200.0f);
	
	piMath::Particle particle;
	particle.position = m_transform.position;
	particle.color = (tag == "enemy") ? piMath::vec3{ 1,0,0 } : piMath::vec3{ 1,1,1 };
	particle.velocity = piMath::vec2{ piMath::Random::onUnitCircle() * piMath::Random::getReal(50.0f, 80.0f) };
	particle.lifeSpan = piMath::Random::getReal(0.15f,0.5f);
	piMath::GetEngine().GetParticleSystem().AddParticle(particle);

	Actor::Update(deltaTime);
}

void Rocket::onCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true; // Destroy the rocket on collision with any other actor
	}
}
