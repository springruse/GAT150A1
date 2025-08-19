#pragma once

#include "SpaceGame.h"
#include "GameData.h"
#include "Enemy.h"
#include "Ally.h"
#include "Engine.h"
#include "Player.h"




bool SpaceGame::Initialize()

{
    m_scene = std::make_unique<claw::Scene>(this);

    claw::json::document_t document;
    claw::json::Load("scene.json", document);
	m_scene->Read(document);

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

    m_scene->Draw(renderer);
    claw::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2.0f;
}



void SpaceGame::SpawnEnemy()
{
//    Player* player = m_scene->GetActorByName<Player>("player");
//
//    if (player) {
//        auto EnemyModel = claw::Resources().Get<claw::Texture>("texture/redShip.png", claw::GetEngine().GetRenderer());
//        
//        claw::vec2 enemyPosition = player->m_transform.position + claw::Random::onUnitCircle() * claw::Random::getReal(300.0f, 500.0f); // points where enemy is allowed to spawn from player
//        claw::Transform transform{ enemyPosition, claw::Random::getReal(0.0f, 360.0f), 1.25f }; // dictates enemy size
//
//        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform); //, EnemyModel);
//        //enemy->damping = 0.98f;
//        enemy->speed = claw::Random::getReal(5.0f, 8.0f);
//        enemy->tag = "enemy";
//        enemy->name = "enemy";
//        enemy->firetimer = 3.0f;
//        enemy->fireTime = 5.0f;
//
//        auto spriteRenderer = std::make_unique<claw::SpriteRenderer>();
//        spriteRenderer->textureName = "texture/redShip.png"; // ship texture
//        enemy->AddComponent(std::move(spriteRenderer));
//
//        auto rb = std::make_unique<claw::RigidBody>();
//        rb->damping = 0.98f; // Damping factor to reduce velocity over time
//        enemy->AddComponent(std::move(rb));
//
//        auto collider = std::make_unique<claw::CircleCollider2D>();
//        collider->radius = 50.0f;
//        enemy->AddComponent(std::move(collider));
//
//        m_scene->AddActor(std::move(enemy));
//    }
}
//
void SpaceGame::SpawnAlly() {
//    Enemy* enemy = m_scene->GetActorByName<Enemy>("enemy");
//
//    if (enemy) {
//        auto allyModel = claw::Resources().Get<claw::Texture>("texture/greenShip.png", claw::GetEngine().GetRenderer());
//
//        claw::vec2 enemyPosition = enemy->m_transform.position + claw::Random::onUnitCircle() * claw::Random::getReal(300.0f, 500.0f); // points where an ally is allowed to spawn near an enemy
//		claw::Transform transform{ enemyPosition, claw::Random::getReal(0.0f, 360.0f), 1.25f }; // dictates ally size
//
//        std::unique_ptr<Ally> ally = std::make_unique<Ally>(transform);//, allyModel);
//        //ally->damping = 0.98f;
//        ally->speed = claw::Random::getReal(8.0f, 10.0f);
//        ally->tag = "player";
//        ally->name = "player";
//        ally->firetimer = 3.0f;
//        ally->fireTime = 5.0f;
//
//        auto spriteRenderer = std::make_unique<claw::SpriteRenderer>();
//        spriteRenderer->textureName = "texture/greenShip.png"; // ship texture
//        ally->AddComponent(std::move(spriteRenderer));
//
//        auto rb = std::make_unique<claw::RigidBody>();
//        rb->damping = 0.98f; // Damping factor to reduce velocity over time
//        ally->AddComponent(std::move(rb));
//
//        auto collider = std::make_unique<claw::CircleCollider2D>();
//        collider->radius = 25.0f;
//        ally->AddComponent(std::move(collider));
//
//        m_scene->AddActor(std::move(ally));
//    }
}
//
void SpaceGame::SpawnPlayer() {
//
//    claw::Transform transform{
//        claw::vec2{
//            claw::GetEngine().GetRenderer().getWidth() * 0.25f,
//            claw::GetEngine().GetRenderer().getHeight() * 0.25f
//        },
//        0.0f,
//        1.5f // change player ship size
//    };
//
//    auto player = std::make_unique<Player>(transform);//, piMath::Resources().Get<piMath::Texture>("texture/blue_01.png", piMath::GetEngine().GetRenderer()));
//    player->speed = 6.0f;
//    player->rotationSpeed = 180.0f;
//    //player->damping = 0.0f;
//    player->fireTime = 50.0f;
//    player->fireTimer = 0.01f;
//    player->SetTransform(transform);
//    player->name = "player";
//    player->tag = "player";
//
//    //components
//    auto spriteRenderer = std::make_unique<claw::SpriteRenderer>();
//    spriteRenderer->textureName = "texture/blue_01.png"; // ship texture
//    player->AddComponent(std::move(spriteRenderer));
//
//    auto rb = std::make_unique<claw::RigidBody>();
//	rb->damping = .99f; // Damping factor to reduce velocity over time
//	player->AddComponent(std::move(rb));
//
//	auto collider = std::make_unique<claw::CircleCollider2D>();
//    collider->radius = 25.0f;
//	player->AddComponent(std::move(collider));
//
//
//
//    m_scene->AddActor(std::move(player));
}
