#include "EnginePCH.h"
#include "AudioSource.h"
#include "Engine.h"
#include "Audio/AudioClip.h"

void claw::AudioSource::Update(float deltatime)
{
	//
}

void claw::AudioSource::Play()
{
	auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());

	if (audioClip) {
		GetEngine().GetAudio().playSound(*audioClip);
	}
}
