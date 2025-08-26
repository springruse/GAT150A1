#include "Scene.h"
#include "Actor.h"
#include "Components/ColliderComponent.h"

namespace claw {

	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	/// 
	void Scene::Update(float dt) {
		// Update each actor in the scene
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}
		// remove destroyed actors
		std::erase_if(m_actors, [](auto& actor) {
			return (actor->destroyed);
			});
		// Check for collisions between actors
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->destroyed) || (actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				// checks if both actors have colliders
				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get()); // Notify actorA of collision with actorB
					actorB->OnCollision(actorA.get()); // Notify actorB of collision with actorA
				}
			}
		}
	}
	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}
	/// <summary>
	/// Adds an actor to the scene.
	/// </summary>
	/// <param name="actor">A shared pointer to the actor to be added to the scene.</param>
	void Scene::AddActor(std::shared_ptr<Actor> actor, bool start) {
		actor->m_scene = this; // Set the scene for the actor
		if (start) {
			actor->Start(); // Call the Start method of the actor
		}
		m_actors.push_back(actor);
	}

	void Scene::RemoveAllActors(bool force) 
	{
		for (auto iterate = m_actors.begin(); iterate != m_actors.end();) {
			if (!(*iterate)->persistent || force) {
				iterate = m_actors.erase(iterate); // Remove actors that are no longer alive
			}
			else {
				++iterate; // Move to the next actor
			}
		}
	}

	bool Scene::Load(const std::string sceneName)
	{
		claw::json::document_t document;
		if (!claw::json::Load(sceneName, document)) {
			Logger::Error("Failed to load scene {} ", sceneName);
			return false;
		}
		//create scene
		Read(document);
		//start actors
		for (auto& actor : m_actors) {
			actor->Start();
		}
		return true;
	}

	void Scene::Read(const json::value_t& value)
	{
		//prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		//actors
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}

}