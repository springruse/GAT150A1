#pragma once

#include "EngineGame/Component.h"

namespace piMath {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;

	};

}