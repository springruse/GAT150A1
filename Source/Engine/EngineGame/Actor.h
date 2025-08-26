#pragma once
#include "Math/Transform.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"
#include "EngineGame/Object.h"
#include "Component.h"
#include "Components/RendererComponent.h"

#include <string>
#include <memory>


namespace claw {
	class Actor : public Object {
		
	public:
		Actor() = default;

		Actor(const Transform& transform) :
			m_transform{ transform }
		{}

		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		virtual void Update(float deltaTime);
		virtual void Draw(class Renderer& renderer);
		virtual void OnCollision(Actor* other);
		virtual void Start();
		virtual void Destroyed();

		Transform GetTransform(){
			return m_transform;
		}
		void SetTransform(const Transform& transform) {
			m_transform = transform;
		}

		float getRadius();

		void Read(const json::value_t& value) override;

	public:
		std::string tag;
		Transform m_transform;
		bool destroyed{ false };
		bool persistent{ false }; 
		float lifeSpan = 0.0f;

		class Scene* m_scene = nullptr;
		

		//components

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

	protected:
		std::vector<std::unique_ptr<class Component>> m_components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) { 
				results.push_back(result); 
			}
		}
		return results;
	}
}