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

		switch (pickupType) {
		case PickupType::POINTS:
			EVENT_NOTIFY_DATA(add_points, value);
			break;
		case PickupType::LIVES:
			EVENT_NOTIFY_DATA(add_lives, value);
			break;
		}

		claw::GetEngine().GetAudio().playSound(soundEffect);
		owner->Destroyed();
	}
}

void Pickup::Read(const claw::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, lifeSpan);
	JSON_READ(value, soundEffect);
	JSON_READ(value, this->value);

	(JSON_READ(value, typeString));
		if (typeString == "points") {
			pickupType = PickupType::POINTS;
		}
		else if (typeString == "lives") {
			pickupType = PickupType::LIVES;
		}
}

void Pickup::OnNotify(const claw::Event& event)
{
	switch (pickupType) {
	case PickupType::POINTS:
		EVENT_NOTIFY_DATA(add_points, value);
		break;
	case PickupType::LIVES:
		EVENT_NOTIFY_DATA(add_lives, value);
		break;
	}
}
