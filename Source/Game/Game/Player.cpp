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

	// rotation speed
	float rotate = 0;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_A))  rotate = -1;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_D))  rotate = +1;

	m_rigidBody->ApplyTorque(rotate * rotationSpeed);

	//thrust speed
	float thrust = 0;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_W))  thrust = +1;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_S))  thrust = -1;
	// player bounds
	owner->m_transform.position.x = claw::Math::Wrap(owner->m_transform.position.x, 0.0f, (float)claw::GetEngine().GetRenderer().getWidth());
	owner->m_transform.position.y = claw::Math::Wrap(owner->m_transform.position.y, 0.0f, (float)claw::GetEngine().GetRenderer().getHeight());

	claw::vec2 force = direction.Rotate(claw::Math::degToRad(owner->m_transform.rotation)) * thrust * speed;
	


	auto* rb = owner->GetComponent<claw::RigidBody>();
	if (rb) {
		rb->ApplyForce(force);
	}

	if (force.Length() > 0) {
		claw::Particle particle;
		particle.position = owner->m_transform.position;
		particle.color = claw::vec3{ 1,1,1 };
		particle.velocity = claw::vec2{ claw::Random::onUnitCircle() * claw::Random::getReal(50.0f, 80.0f) };
		particle.lifeSpan = 1.0f;
		claw::GetEngine().GetParticleSystem().AddParticle(particle);
	}

	// check if player fires
	fireTimer -= dt;
	if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_E))
	{
		fireTimer = fireTime; // Reset fire timer

		auto sound = claw::GetEngine().GetAudio().playSound(*claw::Resources().Get<claw::AudioClip>("shipBlast1.wav", claw::GetEngine().GetAudio()).get());
		if (sound) {
			claw::GetEngine().GetAudio().playSound("shipBlast1.wav");
		}
		auto rocket = claw::Instantiate("rocket", owner->m_transform.position, owner->m_transform.rotation, 1.0f);
		rocket->lifeSpan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "player"; // Set rocket name for identification
	}
}

void Player::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void Player::Read(const claw::json::value_t& value)
{
}
