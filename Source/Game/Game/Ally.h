
#pragma once
#include "EngineGame/Actor.h"
#include "EngineGame/Scene.h"


class Ally : public claw::Component, public claw::ICollidable {
public:
	Ally() = default;
	CLASS_PROTOTYPE(Ally)

	
	float damping = 0.98f;
	float speed = 100;
	claw::vec2 direction = { 0,0 };
	float firetimer = 0.0f; // Timer for firing rockets
	float fireTime = 3.0f; // Time between shots in seconds
	claw::RigidBody* m_rigidBody = nullptr;

public:
	void OnCollision(class claw::Actor* other);
	void Read(const claw::json::value_t& value) override;
	void Update(float deltaTime) override;

};