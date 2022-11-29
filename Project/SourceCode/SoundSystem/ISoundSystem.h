#pragma once
#include "pch.h"
#include <string>
#include <memory>
#include "ISoundProxy.h"

class SOUNDSYSTEM_API ISoundSystem
{
public:
    virtual void LoadSound(const std::string& filename, const std::string& soundName) = 0;
    virtual void UnloadSound(const std::string& soundName) = 0;
    virtual std::unique_ptr<ISoundProxy> CreateProxy() = 0;
    virtual void SetListenerPosition(float px, float py, float pz) = 0;
    virtual void SetListenerVelocity(float vx, float vy, float vz) = 0;
    virtual std::array<float, 3> GetListenerPosition() const = 0;
    virtual std::array<float, 3> GetListenerVelocity() const = 0;
};
