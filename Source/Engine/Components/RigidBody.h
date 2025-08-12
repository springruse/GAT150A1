#pragma once

#include "EngineGame/Component.h"

namespace piMath {
	class RigidBody : public Component {
	public:
		void Update(float dt);
	public:
		vec2 velocity{ 0, 0 };
		float damping{ 0.0f }; 

	};
}