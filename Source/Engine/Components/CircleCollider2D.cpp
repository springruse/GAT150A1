#include "Components/CircleCollider2D.h"
namespace claw {
	void CircleCollider2D::Update(float deltaTime) {
		// Update logic for CircleCollider2D if needed
	}

	bool CircleCollider2D::CheckCollision(ColliderComponent& other) {
		float distance = (owner->m_transform.position - other.owner->m_transform.position).Length();
		auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
		if (circleCollider) {
			float radii = radius + circleCollider->radius;
			if (distance <= radii) {
				return true;
			}
		}
		return false;
		
	}
}