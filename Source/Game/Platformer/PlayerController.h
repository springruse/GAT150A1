#pragma once
#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

#include <memory>

class PlayerController : public claw::Component, public claw::ICollidable {

public:
	PlayerController() = default;
	void Update(float dt) override;
	CLASS_PROTOTYPE(PlayerController)

		claw::RigidBody* m_rigidBody = nullptr;

	// load values from json
	float speed = 0.0;
	float maxSpeed = 0.0;
	float jump = 0.0f;
	//float fireTime = 3.5f;
	//float fireTimer = 3.0f; // Timer for firing rockets

	

	void Start() override;
	void OnCollision(class claw::Actor* other);
	void Read(const claw::json::value_t& value) override;


};