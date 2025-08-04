#pragma once
#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Vector2.h"


#include <memory>

class Player : public piMath::Actor {
	enum class PowerUpType;

public:
	Player() = default;
	Player(const piMath::Transform& transform, std::shared_ptr<piMath::Model> model) :
	
		Actor{transform, model}

	{} 

	void Update(float dt) override;

	float speed = 175;
	float rotationSpeed = 180.0f;
	float fireTime = 3.5f;
	float fireTimer = 3.0f; // Timer for firing rockets
	float damping = 0.98f; // Damping factor to reduce velocity over time

	// Inherited via Actor
	void onCollision(Actor* other) override;
};