#pragma once

#include "SpaceGame.h"
#include <vector>
#include "EngineGame/Game.h"
#include "EngineGame/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "EngineGame/Actor.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "GameData.h"
#include "Enemy.h"
#include "Ally.h"
#include "Engine.h"
#include "Player.h"
#include "Audio/AudioSystem.h"



bool SpaceGame::Initialize()

{
    m_scene = std::make_unique<piMath::Scene>(this);

    m_titleFont = std::make_shared<piMath::Font>();
    m_titleFont->Load("airstrike.ttf", 24);

    m_uiFont = std::make_shared<piMath::Font>();
    m_uiFont->Load("airstrike.ttf", 24);

    m_titleText = std::make_shared<piMath::Text>(m_titleFont);
    m_scoreText = std::make_shared<piMath::Text>(m_uiFont);
    m_livesText = std::make_shared<piMath::Text>(m_uiFont);
    piMath::GetEngine().GetAudio().addSound("wisteria.mp3", "wisteria");
    piMath::GetEngine().GetAudio().addSound("deathSound.wav", "death");
    piMath::GetEngine().GetAudio().addSound("shipBlast1.wav", "blaster");

    std::shared_ptr<piMath::Model> newModel = std::make_shared<piMath::Model>(GameData::squarePoint, piMath::vec3{ 0, 0, 1 });
    
    std::shared_ptr<piMath::Model> EnemyModel = std::make_shared<piMath::Model>(GameData::enemyShipPoints, piMath::vec3{ 1, 0, 0 });

    

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
        if (piMath::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = SpaceGame::GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
    {
        m_score = 0;
        m_lives = 3;
        m_enemySpawnTimer = 0;

        std::shared_ptr<piMath::Model> playerModel = std::make_shared<piMath::Model>(GameData::playerShipPoints, piMath::vec3{ 0, 1, 0 });
        piMath::Transform transform{
            piMath::vec2{
                piMath::GetEngine().GetRenderer().getWidth() * 0.25f,
                piMath::GetEngine().GetRenderer().getHeight() * 0.25f
            },
            0.0f,
            5.0f // change player ship size
        };

        auto player = std::make_unique<Player>(transform, playerModel);
        player->speed = 3.0f;
        player->rotationSpeed = 180.0f;
        player->damping = 0.95f;
        player->fireTime = 50.0f;
        player->fireTimer = 0.01f;
        player->SetTransform(transform);
        player->name = "player";
        player->tag = "player";

        m_scene->AddActor(std::move(player));
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
        SpaceGame::GameState::StartGame;
        break;

    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;

        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
                m_stateTimer = 3;
            }
            else {
                m_gameState = GameState::StartRound;
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
   


    if (piMath::GetEngine().GetInput().getKeyDown(SDL_SCANCODE_X)) {
        piMath::GetEngine().GetTime().setTimeScale(0.5);
    }

    m_scene->Update(piMath::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(piMath::Renderer& renderer)
{
    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "piMath", piMath::vec3{ 0, 0.25f, 0.25f });
        m_scene->Draw(renderer);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "Game Over!", piMath::vec3{ 0, 0.25f, 0.25f });
        m_scene->Draw(renderer);
    }

    m_scoreText->Create(renderer, "SCORE - " + std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20.0f, 20.0f);

    m_livesText->Create(renderer, "LIVES - " + std::to_string(m_lives), { 1, 1, 1 });
    m_livesText->Draw(renderer, (float)(renderer.getWidth() - 200), 20.0f);

    m_scene->Draw(renderer);
    piMath::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy()
{
    Player* player = m_scene->GetActorByName<Player>("player");

    if (player) {
        std::shared_ptr<piMath::Model> EnemyModel = std::make_shared<piMath::Model>(GameData::enemyShipPoints, piMath::vec3{ 1, 0, 0 });
        
        piMath::vec2 enemyPosition = player->m_transform.position + piMath::Random::onUnitCircle() * piMath::Random::getReal(300.0f, 500.0f); // points where enemy is allowed to spawn from player
        piMath::Transform transform{ enemyPosition, piMath::Random::getReal(0.0f, 360.0f), 10.0f }; // 10.0f is the enemy size

        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, EnemyModel);
        enemy->damping = 0.98f;
        enemy->speed = piMath::Random::getReal(2.0f, 3.0f);
        enemy->tag = "enemy";
        enemy->name = "enemy";
        enemy->firetimer = 3.0f;
        enemy->fireTime = 5.0f;

        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::SpawnAlly() {
    Enemy* enemy = m_scene->GetActorByName<Enemy>("enemy");

    if (enemy) {
        std::shared_ptr<piMath::Model> allyModel = std::make_shared<piMath::Model>(GameData::enemyShipPoints, piMath::vec3{ 0, 0.50f, 0 });

        piMath::vec2 enemyPosition = enemy->m_transform.position + piMath::Random::onUnitCircle() * piMath::Random::getReal(300.0f, 500.0f); // points where an ally is allowed to spawn near an enemy
        piMath::Transform transform{ enemyPosition, piMath::Random::getReal(0.0f, 360.0f), 5.0f }; // 10.0f is the enemy size

        std::unique_ptr<Ally> ally = std::make_unique<Ally>(transform, allyModel);
        ally->damping = 0.98f;
        ally->speed = piMath::Random::getReal(5.0f, 8.0f);
        ally->tag = "player";
        ally->name = "player";
        ally->firetimer = 3.0f;
        ally->fireTime = 5.0f;

        m_scene->AddActor(std::move(ally));
    }
}
