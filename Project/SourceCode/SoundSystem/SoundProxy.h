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
<<<<<<< HEAD
#include "ISoundProxy.h"

class SoundSystem;

struct Sound
{
    float duration = 0.0f;
    float time = 0.0f;
    ALuint source = 0u;
};

class SOUNDSYSTEM_API SoundProxy : public ISoundProxy
=======

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
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
{
public:
    SoundProxy(SoundSystem* system) : position_{ 0.0f }, velocity_{ 0.0f }, system_(system) {}
    SoundProxy(const SoundProxy& proxy) = delete;
    SoundProxy(SoundProxy&& proxy) noexcept;
    SoundProxy& operator=(const SoundProxy& proxy) = delete;
    SoundProxy& operator=(SoundProxy&& proxy) noexcept;
<<<<<<< HEAD
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
=======
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
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
    ~SoundProxy();
private:
    float position_[3];
    float velocity_[3];
    SoundSystem* system_;
<<<<<<< HEAD
    std::unordered_map<std::string, Sound> sounds_;
=======
    std::unordered_map<std::string, ALuint> sources_;
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
};
