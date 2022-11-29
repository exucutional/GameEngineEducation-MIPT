#pragma once
#include "pch.h"
#include "SoundProxy.h"
<<<<<<< HEAD
#include "ISoundSystem.h"

class SOUNDSYSTEM_API SoundSystem : public ISoundSystem
=======

class SOUNDSYSTEM_API SoundSystem
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
{
public:
    SoundSystem(const char* deviceName = nullptr);
    SoundSystem(const SoundSystem& system) = delete;
    SoundSystem(SoundSystem&& system) = delete;
    SoundSystem& operator=(const SoundSystem& system) = delete;
    SoundSystem& operator=(SoundSystem&& system) = delete;
<<<<<<< HEAD
    void LoadSound(const std::string& filename, const std::string& soundName) override;
    void UnloadSound(const std::string& soundName) override;
    std::unique_ptr<ISoundProxy> CreateProxy() override;
    void SetListenerPosition(float px, float py, float pz) override;
    void SetListenerVelocity(float vx, float vy, float vz) override;
    std::array<float, 3> GetListenerPosition() const override;
    std::array<float, 3> GetListenerVelocity() const override;
    ALuint GetSoundBuffer(const std::string& soundName) const;
=======
    void LoadFile(const std::string& filename, const std::string& soundName);
    std::unique_ptr<SoundProxy> CreateProxy();
    ALuint GetSoundBuffer(const std::string& soundName) const;
    void SetListenerPosition(float px, float py, float pz);
    std::array<float, 3> GetListenerPosition() const;
    void SetListenerVelocity(float vx, float vy, float vz);
    std::array<float, 3> GetListenerVelocity() const;
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
    ~SoundSystem();
private:
    ALCdevice* device_;
    ALCcontext* context_;
    std::unordered_map<std::string, ALuint> buffers_;
};
