#include "PlatformerGame.h"
#include "Renderer/Renderer.h"

bool PlatformerGame::Initialize()
{
	OBSERVER_ADD("playerDead");
	OBSERVER_ADD("addScore");

	m_scene = std::make_unique<claw::Scene>(this);
	m_scene->Load("scenes/prototypes.json");
	m_scene->Load("scenes/level.json");

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
		break;
	case PlatformerGame::GameState::PlayerDead:
		break;
	case PlatformerGame::GameState::GameOver:
		break;
	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		SpawnEnemy();
		SpawnBat();
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
	claw::GetEngine().GetParticleSystem().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() 
{
}

void PlatformerGame::OnNotify(const claw::Event& event)
{
}

void PlatformerGame::SpawnPlayer() {
	auto player = claw::Instantiate("platformPlayer");
	m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnBat() {
	auto player = claw::Instantiate("bat");
	m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = claw::Instantiate("platformEnemy");
	m_scene->AddActor(std::move(enemy));
}




