#include "EnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Update(float dt)
{
	float dir = 0;

	// move to player
	auto player = owner->m_scene->GetActorByName<claw::Actor>("platformPlayer");
	if (player) {
		if (player->m_transform.position.x < owner->m_transform.position.x) dir = -1;
		else dir = 1;
	}

	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_A))  dir = -1;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_D))  dir = +1;


	if (dir != 0) {
		m_rigidBody->ApplyForce(claw::vec2{ 1,0 } *dir * speed);
	}

	if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->ApplyForce(claw::vec2{ 0,-1 } * speed);
	}
}

void EnemyController::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void EnemyController::OnCollision(class claw::Actor* other)
{
}

void EnemyController::Read(const claw::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, fireTime);
	JSON_READ(value, jump);

}
