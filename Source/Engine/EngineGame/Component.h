#pragma once
#include "EngineGame/Object.h"

namespace claw {
	class Component : public Object {
	public:
		class Actor* owner = nullptr; // Pointer to the owner actor of this component
	public:
		Component() = default;

		virtual void Start() {};
		virtual void Destroyed() {};
		virtual void Update(float deltatime) = 0; // pure virtual
	};
}