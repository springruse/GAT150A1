#pragma once

#include "EngineGame/Actor.h"
#include "Engine.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

#include <memory>

class Pickup : public claw::Component {

public:
	Pickup() = default;
	void Update(float dt) override;
	CLASS_PROTOTYPE(Pickup)

		claw::RigidBody* m_rigidBody = nullptr;

	void Start() override;
	void OnCollision(class claw::Actor* other);
	void Read(const claw::json::value_t& value) override;


};