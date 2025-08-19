#include "EnginePCH.h"
#include "AudioSource.h"
#include "Engine.h"
#include "Audio/AudioClip.h"
namespace claw {
	FACTORY_REGISTER(AudioSource)

	void AudioSource::Update(float deltatime)
	{
		//
	}

	void AudioSource::Play()
	{
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());

		if (audioClip) {
			GetEngine().GetAudio().playSound(*audioClip);
		}
	}
}

