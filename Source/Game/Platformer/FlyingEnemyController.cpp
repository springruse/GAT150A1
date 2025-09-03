#include "FlyingEnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Update(float dt)
{
	float dir = 0;

	// move to player
	auto player = owner->m_scene->GetActorByName<claw::Actor>("platformPlayer");
	if (player) {
		claw::vec2 direction = player->m_transform.position - owner->m_transform.position;
		m_rigidBody->ApplyForce(direction.Normalize() * speed);
	}

	if (dir != 0) {
		m_rigidBody->ApplyForce(claw::vec2{ 1,0 } *dir * speed);
	}

	if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->ApplyForce(claw::vec2{ 0,-1 } *speed);
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
