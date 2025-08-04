#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Model.h"
#include "Scene.h"
namespace piMath {

	void piMath::Actor::Update(float deltaTime)
	{
		if (destroyed) return;

		if (lifeSpan != 0) {
			lifeSpan -= deltaTime;
			destroyed = lifeSpan <= 0.0f;
		}
		m_transform.position += velocity * deltaTime;
		velocity *= (1.0f * (0.992f + damping * deltaTime));
	}

	void piMath::Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		m_model->Draw(renderer, m_transform);
	}
	float Actor::getRadius()
	{
		return (m_model) ? m_model->getRadius() * m_transform.scale * 0.9f : 0.0f;
	}
	inline void piMath::Scene::AddActor(std::shared_ptr<class Actor> actor) {
		m_actors.push_back(actor);
	}

}

