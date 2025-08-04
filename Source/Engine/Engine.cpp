#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Time.h"
#pragma once

namespace piMath {

	Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}

	void piMath::Engine::Update()
	{
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
	}

	bool piMath::Engine::Initialize()
	{
		m_renderer = std::make_unique<piMath::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Game project", 1280, 1024);

		m_input = std::make_unique<piMath::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<piMath::AudioSystem>();
		m_audio->Initialize();

		m_particleSystem = std::make_unique<piMath::ParticleSystem>();
		m_particleSystem->Initialize(5000);

		return true;
	}

	void piMath::Engine::Shutdown()
	{
		m_audio->Shutdown();
		m_particleSystem->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
	}
}
