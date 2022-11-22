#pragma once

#include "pch.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>
#include "sndfile.h"
#include "framework.h"
#include "AL/al.h"
#include "AL/alc.h"

class SoundSystem;

enum class SoundState
{
    Initial,
    Playing,
    Paused,
    Stopped,
    Unknown,
};

class SOUNDSYSTEM_API SoundProxy
{
public:
    SoundProxy(SoundSystem* system) : position_{ 0.0f }, velocity_{ 0.0f }, system_(system) {}
    SoundProxy(const SoundProxy& proxy) = delete;
    SoundProxy(SoundProxy&& proxy) noexcept;
    SoundProxy& operator=(const SoundProxy& proxy) = delete;
    SoundProxy& operator=(SoundProxy&& proxy) noexcept;
    void SetPosition(float px, float py, float pz);
    void SetVelocity(float vx, float vy, float vz);
    std::array<float, 3> GetPosition() const;
    std::array<float, 3> GetVelocity() const;
    void PlaySound(const std::string& soundName);
    void PauseSound(const std::string& soundName);
    SoundState GetSoundState(const std::string& soundName) const;
    void StopSound(const std::string& soundName);
    void StopAllSounds();
    void SetSoundLoop(const std::string& soundName, bool loop);
    void SetSoundGain(const std::string& soundName, float gain);
    ~SoundProxy();
private:
    float position_[3];
    float velocity_[3];
    SoundSystem* system_;
    std::unordered_map<std::string, ALuint> sources_;
};
