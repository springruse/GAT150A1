#pragma once
#include "Resources/Resource.h"
namespace piMath {
	class AudioClip : public Resource{
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& audioSystem);
	private:
		friend class AudioSystem;
		FMOD::Sound* m_sound = nullptr;
	};
}