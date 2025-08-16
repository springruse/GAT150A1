#pragma once
#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
//unfinished but is similar to enemy.h

class Rocket : public claw::Actor {
public:
	Rocket() = default;
	Rocket(const claw::Transform& transform) :
		claw::Actor{ transform }
	{}

	void Update(float deltaTime) override;
	float damping = 1.0f;
	float speed = 100;
	claw::vec2 direction = { 0,0 };

	// Inherited via Actor
	void onCollision(Actor* other) override;

};