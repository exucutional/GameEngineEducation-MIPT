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
#include "ISoundProxy.h"

class SoundSystem;

struct Sound
{
    float duration = 0.0f;
    float time = 0.0f;
    ALuint source = 0u;
};

class SOUNDSYSTEM_API SoundProxy : public ISoundProxy
{
public:
    SoundProxy(SoundSystem* system) : position_{ 0.0f }, velocity_{ 0.0f }, system_(system) {}
    SoundProxy(const SoundProxy& proxy) = delete;
    SoundProxy(SoundProxy&& proxy) noexcept;
    SoundProxy& operator=(const SoundProxy& proxy) = delete;
    SoundProxy& operator=(SoundProxy&& proxy) noexcept;
    void SetPosition(float px, float py, float pz) override;
    void SetVelocity(float vx, float vy, float vz)override;
    std::array<float, 3> GetPosition() const override;
    std::array<float, 3> GetVelocity() const override;
    void PlaySound(const std::string& soundName, float duration = 0) override;
    void PauseSound(const std::string& soundName) override;
    SoundState GetSoundState(const std::string& soundName) const override;
    void StopSound(const std::string& soundName) override;
    void StopAllSounds() override;
    void SetSoundLoop(const std::string& soundName, bool loop) override;
    void SetSoundGain(const std::string& soundName, float gain) override;
    void Update(float dt) override;
    ~SoundProxy();
private:
    float position_[3];
    float velocity_[3];
    SoundSystem* system_;
    std::unordered_map<std::string, Sound> sounds_;
};
