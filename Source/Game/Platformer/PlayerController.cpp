#include "PlayerController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Update(float dt)
{
	float dir = 0;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_A))  dir = -1;
	if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_D))  dir = +1;

	
	if (dir != 0) {
		m_rigidBody->ApplyForce(claw::vec2 {1,0} * dir * speed);
	}

	if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->ApplyForce(claw::vec2{ 0,-1 } * speed);
	}
}

void PlayerController::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void PlayerController::OnCollision(class claw::Actor* other) 
{
}

void PlayerController::Read(const claw::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, fireTime);
	JSON_READ(value, jump);

}
