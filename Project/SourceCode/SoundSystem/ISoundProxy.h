#pragma once
#include "pch.h"
#include <string>

enum class SoundState
{
    Initial,
    Playing,
    Paused,
    Stopped,
    Unknown,
};

class SOUNDSYSTEM_API ISoundProxy
{
public:
    virtual void SetPosition(float px, float py, float pz) = 0;
    virtual void SetVelocity(float vx, float vy, float vz) = 0;
    virtual std::array<float, 3> GetPosition() const = 0;
    virtual std::array<float, 3> GetVelocity() const = 0;
    virtual void PlaySound(const std::string& soundName, float duration = 0.0f) = 0;
    virtual void PauseSound(const std::string& soundName) = 0;
    virtual SoundState GetSoundState(const std::string& soundName) const = 0;
    virtual void StopSound(const std::string& soundName) = 0;
    virtual void StopAllSounds() = 0;
    virtual void SetSoundLoop(const std::string& soundName, bool loop) = 0;
    virtual void SetSoundGain(const std::string& soundName, float gain) = 0;
    virtual void Update(float dt) = 0;
};
