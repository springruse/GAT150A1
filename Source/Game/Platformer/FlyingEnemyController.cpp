#include "FlyingEnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Update(float dt)
{
	

	// move to player
	auto player = owner->m_scene->GetActorByName<claw::Actor>("platformPlayer");
	if (player) {
		claw::vec2 direction = player->m_transform.position - owner->m_transform.position;
		m_rigidBody->ApplyForce(direction.Normalize() * speed);
	}

}

void FlyingEnemyController::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void FlyingEnemyController::OnCollision(class claw::Actor* other)
{
}

void FlyingEnemyController::Read(const claw::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, fireTime);
	JSON_READ(value, jump);

}
