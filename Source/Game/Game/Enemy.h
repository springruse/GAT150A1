#pragma once
#include "EngineGame/Actor.h"
#include "EngineGame/Scene.h"

class Enemy : public piMath::Actor {
public:
	Enemy() = default;
	Enemy(const piMath::Transform& transform, piMath::res_t<piMath::Texture> texture) :
		piMath::Actor{ transform, texture }
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