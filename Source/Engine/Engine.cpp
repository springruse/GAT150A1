#include "Engine.h"

#pragma once

namespace claw {


	void claw::Engine::Update()
	{
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
	}

	void Engine::Draw()
	{

	}

	bool claw::Engine::Initialize()
	{
		m_renderer = std::make_unique<claw::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Game project", 1280, 1024, false);

		m_input = std::make_unique<claw::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<claw::AudioSystem>();
		m_audio->Initialize();

		m_particleSystem = std::make_unique<claw::ParticleSystem>();
		m_particleSystem->Initialize(5000);

		return true;
	}

	void claw::Engine::Shutdown()
	{
		// release all resources
		Resources().Clear();

		m_audio->Shutdown();
		m_particleSystem->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
	}
}
