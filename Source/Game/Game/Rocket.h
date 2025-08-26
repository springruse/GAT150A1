#pragma once
#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"

class Rocket : public claw::Component, public claw::ICollidable {
public:
	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)

	void Update(float deltaTime) override;
	float speed = 100;
	claw::vec2 direction = { 0,0 };

	// Inherited via Actor
	void OnCollision(claw::Actor* other) override;

};