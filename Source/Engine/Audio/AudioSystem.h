#pragma once
#include <fmod.hpp>
#include <string>
#include <map>
 
namespace piMath {
	class AudioSystem {
	public:
		AudioSystem() = default;
		
		bool Initialize();
		void Shutdown();
		void Update();
		
		bool addSound(const std::string& filename, const std::string& name = "");
		bool playSound(const std::string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT result);

	private:
		FMOD::System* m_system = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};

}