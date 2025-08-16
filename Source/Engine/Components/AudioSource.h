#pragma once

#include "EngineGame/Component.h"

namespace claw {
	class AudioSource : public Component {
	public:
		std::string audioClipName;

		
	public:
		void Update(float deltatime) override;

		void Play();
	};
}