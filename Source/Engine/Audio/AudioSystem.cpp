#include "AudioSystem.h"
#include <fmod_errors.h>
#include <../../Core/StringHelper.h>
#include <iostream>

namespace piMath {
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK) {
			std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		return true;
	}
	bool AudioSystem::Initialize()
	{
		FMOD_RESULT result = FMOD::System_Create(&m_system);

		if (!CheckFMODResult(result)) {
			return false;
		}

		result = m_system->init(512, FMOD_INIT_NORMAL, nullptr);
		if (!CheckFMODResult(result)) {
			return false;
		}


		return true;
	}
	
	void AudioSystem::Shutdown()
	{
		CheckFMODResult(m_system->release());
	}
	void AudioSystem::Update()
	{
		FMOD_RESULT result = m_system->update();
		CheckFMODResult(result);
	}

	bool AudioSystem::addSound(const std::string& filename, const std::string& name)
	{

		std::string key = (name.empty() ? filename : name);

		// convert to lowercase
		for (char& c : key) {
			c = std::tolower(c);
		}

		// check if key exists within sounds map
		if (m_sounds.find(key) != m_sounds.end()) {
			std::cerr << "Sound with name '" << key << "' already exists." << std::endl;
			return false;
		}

		FMOD::Sound* sound = nullptr;
		
		// attempt to create sound
		FMOD_RESULT  result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);

		// check if sound was created successfully
		if (!CheckFMODResult(result)) {
			return false;
		}

		//insert sound into map
		m_sounds[key] = sound;

		return true;
	}
	bool AudioSystem::playSound(const std::string& name)
	{
		std::string key = name;

		// convert to lowercase
		for (char& c : key) {
			c = std::tolower(c); 
		}

		// check if sound exists in the map
		if (m_sounds.find(key) == m_sounds.end()) {
			std::cerr << "Sound with name '" << key << "' does not exist." << std::endl;
			return false;
		}
		// play the sound
		FMOD_RESULT result = m_system->playSound(m_sounds[key], 0, false, nullptr);

		if (!CheckFMODResult(result)) return false;

		return true; 
	}
}