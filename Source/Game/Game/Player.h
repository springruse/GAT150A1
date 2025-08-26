#pragma once
#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

#include <memory>

class Player : public claw::Component {

public:
	Player() = default;
	void Update(float dt) override;
	CLASS_PROTOTYPE(Player)

	float speed = 5;
	float rotationSpeed = 180.0f;
	float fireTime = 3.5f;
	float fireTimer = 3.0f; // Timer for firing rockets
	float damping = 0.98f; // Damping factor to reduce velocity over time

	// Inherited via Actor
	void OnCollision(class claw::Actor* other);

	void Read(const claw::json::value_t& value) override;
};	