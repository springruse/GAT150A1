#pragma once
#include "EngineGame/Component.h"

namespace claw {
	class RigidBody : public Component {
	public:
		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };
	public:
		CLASS_PROTOTYPE(RigidBody)

		void Update(float dt);
		void Read(const json::value_t& value) override;

	};
}