#pragma once
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
#include <string>
#include <memory>


namespace piMath {
	class Actor {
	public:
		Actor() = default;
		Actor(const Transform& transform, res_t<Texture> texture) :
			m_transform{ transform },
			m_texture{ texture }
			
		{};

		virtual void Update(float deltaTime);
		virtual void Draw(class Renderer& renderer);
		virtual void onCollision(Actor* other) = 0;

		Transform GetTransform(){
			return m_transform;
		}
		void SetTransform(const Transform& transform) {
			m_transform = transform;
		}

		float getRadius();

	public:

		std::string name;
		std::string tag;
		Transform m_transform;
		vec2 velocity{ 0,0 };
		bool destroyed{ false };
		float lifeSpan = 0.0f;

		class Scene* m_scene = nullptr;

	protected:
		res_t<Texture> m_texture;
		//std::shared_ptr<Model> m_texture;
		
		float damping = 0.98f; // Damping factor to reduce velocity over time
	};
}