#include "AudioSystem.h"
#include <fmod_errors.h>
#include "../Core/StringHelper.h"
#include "../Core/Logger.h"
#include "AudioClip.h"
#include <iostream>

namespace claw {
    bool AudioSystem::CheckFMODResult(FMOD_RESULT result)
    {
        if (result != FMOD_OK) {
            Logger::Error("FMOD Error!" ); // log error result later, breaks on result
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
			Logger::Warning("Sound with name {}" , key , " already exists.");
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
	// play sound using name
	bool AudioSystem::playSound(const std::string& name)
	{
		std::string key = name;

		// convert to lowercase
		for (char& c : key) {
			c = std::tolower(c); 
		}

		// check if sound exists in the map
		if (m_sounds.find(key) == m_sounds.end()) {
			Logger::Warning("Sound with name:" , key , " does not exist.");
			return false;
		}
		// play the sound
		FMOD_RESULT result = m_system->playSound(m_sounds[key], 0, false, nullptr);

		if (!CheckFMODResult(result)) return false;

		return true; 
	}
	// play sound using AudioClip
	bool AudioSystem::playSound(AudioClip& audioClip)
	{
		FMOD_RESULT result = m_system->playSound(audioClip.m_sound, 0, false, nullptr);
		return (!AudioSystem::CheckFMODResult(result));

	}
}