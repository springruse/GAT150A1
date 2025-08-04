#pragma once
#include <memory>
#include "../Renderer/Renderer.h"

namespace piMath {
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(piMath::Renderer& renderer) = 0;

		void addPoints(int points) { m_score += points; }
		int getPoints() const { return m_score; }


		void addLives(int lives) { m_lives += lives; }
		int getLives() const { return m_lives; }
	protected:
		int m_score = 0; // Game score
		int m_lives = 3; // Player lives
		std::unique_ptr<class Scene> m_scene;
	};
}