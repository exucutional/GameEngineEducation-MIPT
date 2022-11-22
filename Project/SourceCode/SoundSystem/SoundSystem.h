#pragma once
#include "pch.h"
#include "SoundProxy.h"

class SOUNDSYSTEM_API SoundSystem
{
public:
    SoundSystem(const char* deviceName = nullptr);
    SoundSystem(const SoundSystem& system) = delete;
    SoundSystem(SoundSystem&& system) = delete;
    SoundSystem& operator=(const SoundSystem& system) = delete;
    SoundSystem& operator=(SoundSystem&& system) = delete;
    void LoadFile(const std::string& filename, const std::string& soundName);
    std::unique_ptr<SoundProxy> CreateProxy();
    ALuint GetSoundBuffer(const std::string& soundName) const;
    void SetListenerPosition(float px, float py, float pz);
    std::array<float, 3> GetListenerPosition() const;
    void SetListenerVelocity(float vx, float vy, float vz);
    std::array<float, 3> GetListenerVelocity() const;
    ~SoundSystem();
private:
    ALCdevice* device_;
    ALCcontext* context_;
    std::unordered_map<std::string, ALuint> buffers_;
};
