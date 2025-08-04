#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "../Renderer/Renderer.h"

namespace piMath {

	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		// Update each actor in the scene
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}
		// remove destroyed actors
		for (auto iterate = m_actors.begin(); iterate != m_actors.end();) {
			if ((*iterate)->destroyed) {
				iterate = m_actors.erase(iterate) ; // Remove actors that are no longer alive
			}
			else {
				++iterate; // Move to the next actor
			}
		}
		// Check for collisions between actors
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->destroyed) || (actorB->destroyed)) continue;
				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();

				if (distance <= actorA->getRadius() + actorB->getRadius()){
					actorA->onCollision(actorB.get()); // Notify actorA of collision with actorB
					actorB->onCollision(actorA.get()); // Notify actorB of collision with actorA

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
			actor->Draw(renderer);
		}
	}
	/// <summary>
	/// Adds an actor to the scene.
	/// </summary>
	/// <param name="actor">A shared pointer to the actor to be added to the scene.</param>
	void Scene::AddActor(std::shared_ptr<Actor> actor) {
		actor->m_scene = this; // Set the scene for the actor
		m_actors.push_back(actor);
	}

	void Scene::RemoveAllActors() 
	{
		m_actors.clear(); // Clear all actors from the scene
	}

}