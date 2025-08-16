#pragma once

#include "EngineGame/Component.h"

namespace claw {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;

	};

}