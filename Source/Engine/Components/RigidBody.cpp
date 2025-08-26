#include "RigidBody.h"

namespace claw {

	FACTORY_REGISTER(RigidBody)

	void claw::RigidBody::Update(float deltaTime) {
		owner->m_transform.position += velocity * deltaTime;
		velocity *= damping; // ( <1) = slower, ( >1) = faster
	}
	void RigidBody::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, damping);
		JSON_READ(value, velocity);
	}
}