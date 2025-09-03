#include "Pickup.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Pickup)

void Pickup::Update(float dt) 
{

}

void Pickup::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void Pickup::OnCollision(class claw::Actor* other)
{
}

void Pickup::Read(const claw::json::value_t& value)
{
}