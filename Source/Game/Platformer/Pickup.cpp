#include "Pickup.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Pickup)

void Pickup::Update(float dt) 
{
	lifeSpan -= dt;
}

void Pickup::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void Pickup::OnCollision(class claw::Actor* other)
{
	if (claw::EqualsIgnoreCase(other->tag, "player")) {
		owner->Destroyed();
	}
}

void Pickup::Read(const claw::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, lifeSpan);
}