
#pragma once
#include "EngineGame/Actor.h"
#include "EngineGame/Scene.h"

class Ally : public piMath::Actor {
public:
	Ally() = default;
	Ally(const piMath::Transform& transform, std::shared_ptr<class piMath::Model> model) :
		piMath::Actor{ transform, model }
	{}

	void Update(float deltaTime) override;
	float damping = 0.98f;
	float speed = 100;
	piMath::vec2 direction = { 0,0 };
	float firetimer = 0.0f; // Timer for firing rockets
	float fireTime = 3.0f; // Time between shots in seconds

	// Inherited via Actor
	void onCollision(Actor* other) override;

};