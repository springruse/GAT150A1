#pragma once
#include "EngineGame/Actor.h"
#include "EngineGame/Scene.h"
#include "EngineGame/Component.h"

class Enemy : public claw::Component, public claw::ICollidable, public claw::IObserver {
public:
	float damping = 0.98f;
	float speed = 100;
	claw::vec2 direction = { 0,0 };
	float fireTimer = 0.0f; // Timer for firing rockets
	float fireTime = 3.0f; // Time between shots in seconds
	claw::RigidBody* m_rigidBody = nullptr;

public:
	CLASS_PROTOTYPE(Enemy)
	Enemy() = default;
	void Start() override;
	void Update(float deltaTime) override;
	void Read(const claw::json::value_t& value) override;

	// Inherited via ICollidable
	void OnCollision(claw::Actor* other) override;

	// Inherited via IObserver
	void OnNotify(const claw::Event& event) override;
};