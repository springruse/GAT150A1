#include "Pickup.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Pickup)

void Pickup::Update(float dt) 
{
	lifeSpan -= dt;

	if (lifeSpan <= 0.0f) {
		owner->Destroyed();
	}
}

void Pickup::Start()
{
	m_rigidBody = owner->GetComponent<claw::RigidBody>();
}

void Pickup::OnCollision(class claw::Actor* other)
{
	if (claw::EqualsIgnoreCase(other->tag, "player")) {
		EVENT_NOTIFY_DATA(add_points, 1);
		owner->Destroyed();
	}
}

void Pickup::Read(const claw::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, lifeSpan);
}

void Pickup::OnNotify(const claw::Event& event)
{
	EVENT_NOTIFY_DATA(add_points, 1);
}
