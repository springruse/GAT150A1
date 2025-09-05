#include "PlatformerGame.h"
#include "Renderer/Renderer.h"
#include "EnginePCH.h"
#include "Engine.h"

bool PlatformerGame::Initialize()
{
	OBSERVER_ADD(add_lives);
	OBSERVER_ADD(add_points);

	m_scene = std::make_unique<claw::Scene>(this);
	m_scene->Load("scenes/prototypes.json");
	m_scene->Load("scenes/level.json");

	m_scoreText = std::make_shared<claw::Text>(claw::Resources().GetWithID<claw::Font>("score", "airstrike.ttf", 24.0f));
	m_livesText = std::make_shared<claw::Text>(claw::Resources().GetWithID<claw::Font>("lives", "airstrike.ttf", 24.0f));
	claw::GetEngine().GetAudio().addSound("pickupCoin.wav", "pickupCoin");
	claw::GetEngine().GetAudio().addSound("fishingrodcast.mp3", "castRod");
	claw::GetEngine().GetAudio().addSound("wilderness.mp3", "wilderness");
	claw::GetEngine().GetAudio().addSound("jingleLoss.wav", "jingleLoss");
	claw::GetEngine().GetAudio().addSound("jingleWin.wav", "jingleWin");
	claw::GetEngine().GetAudio().addSound("waterSplash.wav", "waterSplash");
	claw::GetEngine().GetAudio().addSound("crateBreak.wav", "crateBreak");

	return true;
}

void PlatformerGame::Shutdown()
{
}

void PlatformerGame::Update(float dt)
{
	
	switch (m_gameState)
	{
	case PlatformerGame::GameState::Init:
		m_gameState = GameState::StartRound;
		break;
	case PlatformerGame::GameState::Title:
		break;
	case PlatformerGame::GameState::StartGame:
		break;
	case PlatformerGame::GameState::Game:
	{
		m_coinSpawnTimer -= dt;
		if (m_coinSpawnTimer <= 0.0f) {
			m_coinSpawnTimer = 3.0f;
			SpawnCoin();
		}
	}
		break;
	case PlatformerGame::GameState::PlayerDead:
		break;
	case PlatformerGame::GameState::GameOver:
		break;
	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		SpawnBat();
		claw::GetEngine().GetAudio().playSound("wilderness");
		m_score = 0;
		m_lives = 0;
		m_gameState = GameState::Game;
		break;
	default:
		break;
	}
	m_scene->Update(claw::GetEngine().GetTime().GetDeltaTime());
	
}

void PlatformerGame::Draw(claw::Renderer& renderer)
{
	m_scene->Draw(renderer);
	m_scoreText->Create(renderer, "MONEY - " + std::to_string(m_score), { 1, 1, 1 });
	m_scoreText->Draw(renderer, 20.0f, 20.0f);

	m_livesText->Create(renderer, "BOXES FISHED - " + std::to_string(m_lives), { 1, 1, 1 });
	m_livesText->Draw(renderer, (float)(renderer.getWidth() - 250), 20.0f);


	claw::GetEngine().GetParticleSystem().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() 
{
}

void PlatformerGame::OnNotify(const claw::Event& event)
{
	if (claw::EqualsIgnoreCase(event.id, "add_points")) {
		addPoints(std::get<int>(event.data));
	}
	if (claw::EqualsIgnoreCase(event.id, "add_lives")) {
		m_lives++;
		addLives(std::get<int>(event.data));
	}
}

void PlatformerGame::SpawnPlayer() {
	auto player = claw::Instantiate("platformPlayer");
	m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnBox()
{
	auto crate = claw::Instantiate("crate");
	m_scene->AddActor(std::move(crate));
}

void PlatformerGame::SpawnBat() {
	auto bat = claw::Instantiate("bat");
	m_scene->AddActor(std::move(bat));
}

void PlatformerGame::SpawnCoin()
{
	auto pickup = claw::Instantiate("coin_get");
	pickup->m_transform.position = claw::vec2{ claw::Random::getReal(10.0f, 1080.f), claw::Random::getReal(0.0f,200.f) };
	m_scene->AddActor(std::move(pickup));
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = claw::Instantiate("platformEnemy");
	m_scene->AddActor(std::move(enemy));
}





