#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Actor.h"
#include "../Core/StringHelper.h"


namespace piMath {
	
	class Actor;
	class Game;

	class Scene {
	public:
		

		Scene(Game* game) : m_game{ game } {}
		
		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::shared_ptr<class Actor> actor);

		void RemoveAllActors();

		template <typename T = Actor>
		T* GetActorByName(const std::string& name);

		template <typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		class Game* GetGame() {
			return m_game; // Returns the game instance associated with the scene
		}

	private:
		std::list<std::shared_ptr<class Actor>> m_actors;
		class Game* m_game = nullptr; // Pointer to the game instance, if needed
	};
	/// <summary>
	/// Retrieves a pointer to an actor of the specified type with the given name from the scene.
	/// </summary>
	/// <typeparam name="T">The type of actor to retrieve.</typeparam>
	/// <param name="name">The name of the actor to search for (case-insensitive).</param>
	/// <returns>A pointer to the actor of type T with the specified name if found; otherwise, returns nullptr.</returns>
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{

		for (auto& Actor : m_actors) {
			if (piMath::toLower(Actor->name) == piMath::toLower(name)) {
				T* object = dynamic_cast<T*>(Actor.get());
				if (object) {
					return object;
				}
			}
		}

		return nullptr;
	}

	/// <summary>
	/// Retrieves all actors in the scene with a matching tag and of a specified type.
	/// </summary>
	/// <typeparam name="T">The type to which the actors should be cast. Only actors of this type will be included in the results.</typeparam>
	/// <param name="tag">The tag to search for among the actors.</param>
	/// <returns>A vector of pointers to actors of type T whose tag matches the specified tag (case-insensitive).</returns>
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;

		for (auto& Actor : m_actors) {
			if (toLower(Actor->tag) == toLower(tag)) {
				T* object = dynamic_cast<T*>(Actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}

		return results;
	}
}


	