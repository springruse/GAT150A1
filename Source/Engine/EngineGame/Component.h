#pragma once
#include "EngineGame/Object.h"

namespace piMath {
	class Component : public Object {
	public:
		class Actor* owner = nullptr; // Pointer to the owner actor of this component
	public:
		Component() = default;
		virtual void Update(float deltatime) = 0; // pure virtual
	};
}