#pragma once
#include "Components/ColliderComponent.h"
namespace piMath {
	class CircleCollider2D : public ColliderComponent {
	public:
		void Update(float deltaTime);

		float radius = 0.0f;
		bool CheckCollision(ColliderComponent& other) override;
	};
}