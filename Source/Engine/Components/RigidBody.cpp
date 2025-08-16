#include "RigidBody.h"

namespace claw {
	void RigidBody::Update(float deltaTime) {
		owner->m_transform.position += velocity * deltaTime;
		velocity *= damping; // ( <1) = slower, ( >1) = faster
	}
}