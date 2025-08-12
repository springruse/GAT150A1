#include "RigidBody.h"

namespace piMath {
	void RigidBody::Update(float deltaTime) {
		owner->m_transform.position += velocity * deltaTime;
		velocity += (1.0f / (1.0f + damping * deltaTime)); // ( <1) = slower, ( >1) = faster
	}
}