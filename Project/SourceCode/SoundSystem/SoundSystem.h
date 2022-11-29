#pragma once
#include "pch.h"
#include "SoundProxy.h"
#include "ISoundSystem.h"

class SOUNDSYSTEM_API SoundSystem : public ISoundSystem
{
public:
    SoundSystem(const char* deviceName = nullptr);
    SoundSystem(const SoundSystem& system) = delete;
    SoundSystem(SoundSystem&& system) = delete;
    SoundSystem& operator=(const SoundSystem& system) = delete;
    SoundSystem& operator=(SoundSystem&& system) = delete;
    void LoadSound(const std::string& filename, const std::string& soundName) override;
    void UnloadSound(const std::string& soundName) override;
    std::unique_ptr<ISoundProxy> CreateProxy() override;
    void SetListenerPosition(float px, float py, float pz) override;
    void SetListenerVelocity(float vx, float vy, float vz) override;
    std::array<float, 3> GetListenerPosition() const override;
    std::array<float, 3> GetListenerVelocity() const override;
    ALuint GetSoundBuffer(const std::string& soundName) const;
    ~SoundSystem();
private:
    ALCdevice* device_;
    ALCcontext* context_;
    std::unordered_map<std::string, ALuint> buffers_;
};
