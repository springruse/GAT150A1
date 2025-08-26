#pragma once
#include "Components/ColliderComponent.h"
namespace claw {
	class CircleCollider2D : public ColliderComponent {
	public:
		CLASS_PROTOTYPE(CircleCollider2D)
		float radius = 0.0f;
		
	public:
		bool CheckCollision(ColliderComponent& other) override;
		void Read(const json::value_t& value) override;
		void Update(float deltaTime);
	};
}