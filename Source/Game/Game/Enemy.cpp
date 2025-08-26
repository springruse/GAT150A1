#include "../GamePCH.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Start()
{
	OBSERVER_ADD("playerDead");
	claw::EventManager::Instance().AddObserver("playerDead", *this);
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
	fireTimer = fireTime;
}

void Enemy::Update(float deltaTime)
{
	bool playerSeen = false;
	claw::Actor* player = owner->m_scene->GetActorByName("player");

	if (player) {
		bool playerSeen = false;

		Player* player = owner->m_scene->GetActorByName<Player>("player");
		if (player) {
			claw::vec2 direction{ 0, 0 };
			direction = player->owner->m_transform.position - owner->m_transform.position;

			direction = direction.Normalize();
			claw::vec2 forward = claw::vec2{ 1, 0 }.Rotate(claw::Math::degToRad(owner->m_transform.rotation));

			float angle = claw::Math::radToDeg(claw::vec2::AngleBetween(forward, direction));
			playerSeen = angle <= 45; // angle threshold for player detection

			if (playerSeen) {
				float angle = claw::vec2::SignedAngleBetween(forward, direction);
				angle = claw::Math::Sign(angle);
				owner->m_transform.rotation += claw::Math::radToDeg(angle * 5 * deltaTime);
			}
		}
	}

	claw::vec2 force = claw::vec2{ 1,0 }.Rotate(claw::Math::degToRad(owner->m_transform.rotation)) * speed;
	//velocity += force; * dt;
	auto* rb = owner->GetComponent<claw::RigidBody>();
	if (rb) {
		rb->velocity += force;
	}

	owner->m_transform.position.x = claw::Math::Wrap(owner->m_transform.position.x, 0.0f, (float)claw::GetEngine().GetRenderer().getWidth());
	owner->m_transform.position.y = claw::Math::Wrap(owner->m_transform.position.y, 0.0f, (float)claw::GetEngine().GetRenderer().getHeight());

	fireTimer = deltaTime;

	if (fireTimer <= 0 && playerSeen)
	{
		fireTimer = fireTime;
		auto rocketModel = claw::Resources().Get<claw::Texture>("texture/redShip.png", claw::GetEngine().GetRenderer());
		auto rocket = claw::Instantiate("rocket", owner->m_transform.position, owner->m_transform.rotation, 1.0f);

		rocket->lifeSpan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy"; 
		owner->m_scene->AddActor(std::move(rocket));
	}
}

void Enemy::OnCollision(claw::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true; 
		claw::EventManager::Instance().Notify({ "addScore", true });
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

void Enemy::OnNotify(const claw::Event& event)
{
	EVENT_NOTIFY_DATA(add_points, 100);
	if (claw::equalsIgnoreCase(event.id, "playerDead")) {
		owner->destroyed = true; // Destroy enemy when player dies
	}
}

void Enemy::Read(const claw::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, damping);
	JSON_READ(value, fireTime);
}


