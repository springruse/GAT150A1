#include "Actor.h"
#include <string>

namespace claw {
	FACTORY_REGISTER(Actor)

	Actor::Actor(const Actor& other) :
		Object{ other },
		tag{ other.tag },
		lifeSpan{ other.lifeSpan },
		m_transform{ other.m_transform }
	{
		//copy components
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

	void Actor::OnCollision(Actor* other) {
		auto collidables = GetComponents<ICollidable>();
		for (auto& collidables : collidables) {
			collidables->OnCollision(other);
		}
	}

		void claw::Actor::Update(float deltaTime)
	{
		if (destroyed) return;

		if (lifeSpan > 0) {
			lifeSpan -= deltaTime;

			if (lifeSpan <= 0) {
				destroyed = true;
				return;
			}

			destroyed = lifeSpan <= 0.0f;
		}
		// update components
		for (auto& component : m_components) {
			if (component->active) {
				component->Update(deltaTime);
			}
		}
	}

	void claw::Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		for (auto& component : m_components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}
		// renderer.DrawTexture(m_texture.get(), m_transform.position.x, m_transform.position.y);
	}

	void Actor::Start()
	{
		for (auto& component : m_components) {
			component->Start();
		}
	}
	void Actor::Destroyed()
	{
		for (auto& component : m_components) {
			component->Destroyed();
		}
	}
	float Actor::getRadius()
	{
		return 25.0f;
	}

	inline void claw::Scene::AddActor(std::shared_ptr<class Actor> actor, bool start) {
		m_actors.push_back(actor);
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		m_components.push_back(std::move(component));
	}
	void Actor::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ(value, tag);
		JSON_READ(value, lifeSpan);
		JSON_READ(value, persistent);
		// transform
		if (JSON_HAS(value, transform)) m_transform.Read(JSON_GET(value, transform));

		//components
		if (JSON_HAS(value, m_components)) {
			for (auto& componentValue : JSON_GET(value, m_components).GetArray()) {
				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}

