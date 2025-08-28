#include "../GamePCH.h"
#include "Rocket.h"

namespace claw
{
	FACTORY_REGISTER(Rocket)
}

void Rocket::Update(float deltaTime)
{
	claw::vec2 force = claw::vec2{ 1,0 }.Rotate(claw::Math::degToRad(owner->m_transform.rotation)) * speed;
	//velocity += force;
	auto* rb = owner->GetComponent<claw::RigidBody>();
	if (rb) {
		rb->SetVelocity(force);
	}

	float angle = owner->m_transform.rotation + claw::Random::getReal(-30.0f, 30.0f);
	claw::vec2 velocity = claw::vec2{ 1,0 }.Rotate(claw::Math::degToRad(angle));
	velocity += claw::Random::getReal(100.0f, 200.0f);
	
	claw::Particle particle;
	particle.position = owner->m_transform.position;
	particle.color = (owner->tag == "enemy") ? claw::vec3{ 1,0,0 } : claw::vec3{ 1,1,1 };
	particle.velocity = claw::vec2{ claw::Random::onUnitCircle() * claw::Random::getReal(50.0f, 80.0f) };
	particle.lifeSpan = claw::Random::getReal(0.15f,0.5f);
	claw::GetEngine().GetParticleSystem().AddParticle(particle);


}

void Rocket::OnCollision(claw::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true; // Destroy the rocket on collision with any other actor
	}
}
