#include "Actor.h"

namespace piMath {

	void piMath::Actor::Update(float deltaTime)
	{
		if (destroyed) return;

		if (lifeSpan > 0) {
			lifeSpan -= deltaTime;

			if (lifeSpan <= 0 ){
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

	void piMath::Actor::Draw(Renderer& renderer)
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
	float Actor::getRadius()
	{
		return 25.0f;//return (m_texture) ? m_texture->GetSize().Length() * 0.5f * m_transform.scale * 0.9f : 0.0f;
	}
	inline void piMath::Scene::AddActor(std::shared_ptr<class Actor> actor) {
		m_actors.push_back(actor);
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		m_components.push_back(std::move(component));
	}
}

