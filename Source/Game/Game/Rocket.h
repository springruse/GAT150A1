#pragma once
#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
//unfinished but is similar to enemy.h

class Rocket : public piMath::Actor {
public:
	Rocket() = default;
	Rocket(const piMath::Transform& transform, std::shared_ptr<class piMath::Model> model) :
		piMath::Actor{ transform, model }
	{}

	void Update(float deltaTime) override;
	float damping = 1.0f;
	float speed = 100;
	piMath::vec2 direction = { 0,0 };

	// Inherited via Actor
	void onCollision(Actor* other) override;

};