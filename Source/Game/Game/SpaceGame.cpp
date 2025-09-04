#pragma once

#include "SpaceGame.h"
#include "GameData.h"
#include "Enemy.h"
#include "Ally.h"
#include "Engine.h"
#include "Player.h"
#include <EngineMinimal.h>




bool SpaceGame::Initialize()

{
    OBSERVER_ADD("playerDead");
	OBSERVER_ADD("addScore");

    m_scene = std::make_unique<claw::Scene>(this);
	m_scene->Load("scene.json");
   

    m_titleText = std::make_shared<claw::Text>(claw::Resources().GetWithID<claw::Font>("title", "airstrike.ttf", 98.0f));
    m_gameOverText = std::make_shared<claw::Text>(claw::Resources().GetWithID<claw::Font>("gameOver", "airstrike.ttf", 98.0f));
    m_scoreText = std::make_shared<claw::Text>(claw::Resources().GetWithID<claw::Font>("score","airstrike.ttf", 24.0f));
    m_livesText = std::make_shared<claw::Text>(claw::Resources().GetWithID<claw::Font>("lives", "airstrike.ttf", 24.0f));
    claw::GetEngine().GetAudio().addSound("wisteria.mp3", "wisteria");
    claw::GetEngine().GetAudio().addSound("deathSound.wav", "death");
    claw::GetEngine().GetAudio().addSound("shipBlast1.wav", "blaster");

    return true;
}

void SpaceGame::Shutdown()
{
    //
}

void SpaceGame::Update(float dt)
{
    

    switch (m_gameState)
    {
    case SpaceGame::GameState::Init:
        m_gameState = SpaceGame::GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = SpaceGame::GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
    {
        m_score = 0;
        m_lives = 3;
        m_enemySpawnTimer = 0;
        SpawnPlayer();

        m_gameState = SpaceGame::GameState::Game;
        break;
    }

    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0.0f) {
            m_enemySpawnTimer = 3.0f;
            SpawnEnemy();
            SpawnAlly();
        }
        break;
        

    case SpaceGame::GameState::StartRound:
        m_scene->RemoveAllActors(false);
        SpawnPlayer();
        m_gameState = SpaceGame::GameState::Game;
        break;

    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;

        if (m_stateTimer <= 0.0f) {
            m_lives--;
            if (m_lives == 0.0f) {
                m_gameState = GameState::GameOver;
				m_stateTimer = 3.0f;
            }
            else {
                m_gameState = GameState::StartRound;
                m_stateTimer = 3.0f;
            }
        }

        break;

    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0.0f) {
            m_gameState = GameState::Title;
            m_scene->RemoveAllActors();
        }
        break;

    default:
        break;
    }

    if (claw::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_X)) { // slow motion
        claw::GetEngine().GetTime().setTimeScale(0.5);
    }

    m_scene->Update(claw::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(claw::Renderer& renderer)
{
    m_scene->Draw(renderer);

    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "phighting the game", claw::vec3{ 1.0f, 1.0f, 1.0f });
        m_titleText->Draw(renderer, 100.0f, 300.0f);
    }

    if (m_gameState == GameState::GameOver) {
        m_gameOverText->Create(renderer, "Game Over!", claw::vec3{ 1.0f, 1.0f, 1.0f });
		m_gameOverText->Draw(renderer, 300.0f, 300.0f);
    }

    m_scoreText->Create(renderer, "SCORE - " + std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20.0f, 20.0f);

    m_livesText->Create(renderer, "LIVES - " + std::to_string(m_lives), { 1, 1, 1 });
    m_livesText->Draw(renderer, (float)(renderer.getWidth() - 200), 20.0f);

    claw::GetEngine().GetParticleSystem().Draw(renderer);
}


void SpaceGame::OnNotify(const claw::Event& event)
{
    if (claw::EqualsIgnoreCase(event.id, "playerDead")) {
        OnPlayerDeath();
    }
    else if ( claw::EqualsIgnoreCase(event.id, "addScore")) {
		addPoints(std::get<int>(event.data));
	}

}


void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2.0f;
}
// enemy
void SpaceGame::SpawnEnemy()
{
	claw::Actor* player = m_scene->GetActorByName("playerA");
    if (player) {
        claw::vec2 enemyPosition = player->m_transform.position + claw::Random::onUnitCircle() * claw::Random::getReal(300.0f, 500.0f); // points where enemy is allowed to spawn from player
        claw::Transform transform{ enemyPosition, claw::Random::getReal(0.0f, 360.0f), 1.25f }; // dictates enemy size
        auto enemy = claw::Instantiate("enemy", enemyPosition, 0, 1.5);
        m_scene->AddActor(std::move(enemy));
    }
}
// ally
void SpaceGame::SpawnAlly() {
    auto ally = claw::Instantiate("ally", claw::vec2{ 40,30 }, 0, 1.25 );
    m_scene->AddActor(std::move(ally));
}
// player
void SpaceGame::SpawnPlayer() {
    auto player = claw::Instantiate("playerA", claw::vec2{ 60,30 }, 0, 1.35f );
    m_scene->AddActor(std::move(player));
}

