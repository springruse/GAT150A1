
#pragma once
#include "EngineGame/Actor.h"
#include "EngineGame/Scene.h"


class Ally : public claw::Component {
public:
	Ally() = default;
	//Ally(const claw::Transform& transform) :
	//	claw::Actor{ transform }
	//{}

	void Update(float deltaTime) override;
	float damping = 0.98f;
	float speed = 100;
	claw::vec2 direction = { 0,0 };
	float firetimer = 0.0f; // Timer for firing rockets
	float fireTime = 3.0f; // Time between shots in seconds

	// Inherited via Actor
	void onCollision(class claw::Actor* other);

};