#pragma once
#include "EngineGame/Game.h"
#include "Renderer/font.h"
#include "Renderer/text.h"

class SpaceGame : public piMath::Game {

	public:
		enum class GameState {
			Init,
			Title,
			StartGame,
			Game,
			PlayerDead,
			GameOver,
			StartRound, // New state for starting a round
		};

	public:
		SpaceGame() = default;

		bool Initialize() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(piMath::Renderer& renderer) override;

		void OnPlayerDeath();

		int m_score = 0; // Player's score
		int m_lives = 0; // Player's lives

	private:
		GameState m_gameState = GameState::Init;
		float m_enemySpawnTimer = 0.0f; // Timer for enemy spawning

		float m_stateTimer = 0.0f; // Timer for state transitions

		std::shared_ptr <class piMath::Font>  m_titleFont;
		std::shared_ptr <class piMath::Font>  m_uiFont;
		std::shared_ptr <class piMath::Text>  m_titleText;
		std::shared_ptr <class piMath::Text>  m_scoreText;
		std::shared_ptr <class piMath::Text>  m_livesText;
	private:
	void SpawnEnemy();
	void SpawnAlly();
};