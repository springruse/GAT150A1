#pragma once

#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

#include <memory>

class Pickup : public claw::Component, public claw::ICollidable, public claw::IObserver {

public:
	Pickup() = default;
	void Update(float dt) override;
	CLASS_PROTOTYPE(Pickup)

		claw::RigidBody* m_rigidBody = nullptr;

	enum class PickupType 
	{
		POINTS,
		LIVES
	};

	float lifeSpan = 0;
	std::string soundEffect = "";
	PickupType pickupType = PickupType::POINTS;  // Default to points
	int value = 1;
	std::string typeString = "";



	void Start() override;
	void OnCollision(class claw::Actor* other);
	void Read(const claw::json::value_t& value) override;

	void OnNotify(const claw::Event& event) override;
};