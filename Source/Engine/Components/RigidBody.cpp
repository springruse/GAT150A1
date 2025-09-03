#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "Engine.h"

namespace claw {

	FACTORY_REGISTER(RigidBody)

	RigidBody::RigidBody(const RigidBody& other)
	{
		bodyDef = other.bodyDef;
		size = other.size;

		if (other.m_physicsBody) {
			m_physicsBody = std::make_unique<PhysicsBody>(*other.m_physicsBody);
		}
	}

	void RigidBody::Start()
	{
		bodyDef.actor = owner;
		if (size.x == 0 && size.y == 0) {
			auto spriteRenderer = owner->GetComponent<SpriteRenderer>();
			if (spriteRenderer) {
				size = spriteRenderer->texture->GetSize();
			}
		}
		m_physicsBody = std::make_unique<PhysicsBody>(owner->m_transform, size * scale, bodyDef, GetEngine().GetPhysics());
	}

	void claw::RigidBody::Update(float deltaTime) {
		owner->m_transform.position = m_physicsBody->GetPosition();
		owner->m_transform.rotation = Math::radToDeg(m_physicsBody->GetAngle());

		velocity = m_physicsBody->GetVelocity();

		//owner->m_transform.position += velocity * deltaTime;
		//velocity *= damping; // ( <1) = slower, ( >1) = faster
	}
	void RigidBody::Read(const json::value_t& value)
	{	
		Object::Read(value);
		JSON_READ(value, size);
		JSON_READ(value, scale);


		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);
		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);
		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);
		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", bodyDef.friction);
		JSON_READ_NAME(value, "restitution", bodyDef.restitution);
		JSON_READ_NAME(value, "density", bodyDef.density);
		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {
			if (EqualsIgnoreCase(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;
			else if (EqualsIgnoreCase(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (EqualsIgnoreCase(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}

	void RigidBody::ApplyForce(const vec2& force) {
		m_physicsBody->ApplyForce(force);
	}

	void RigidBody::ApplyTorque(float radians) {
		m_physicsBody->ApplyTorque(radians);
	}
	
	void RigidBody::SetVelocity(const vec2& velocity) {
		m_physicsBody->SetVelocity(velocity);
	}
}