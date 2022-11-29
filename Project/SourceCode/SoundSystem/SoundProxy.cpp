#include "pch.h"
#include <cassert>
#include "SoundProxy.h"
#include "SoundSystem.h"
#include <array>

SoundProxy::SoundProxy(SoundProxy&& proxy) noexcept :
    system_(std::move(proxy.system_)),
    sounds_(std::move(proxy.sounds_))
{
    position_[0] = proxy.position_[0];
    position_[1] = proxy.position_[1];
    position_[2] = proxy.position_[2];
    velocity_[0] = proxy.velocity_[0];
    velocity_[1] = proxy.velocity_[1];
    velocity_[2] = proxy.velocity_[2];
}

SoundProxy& SoundProxy::operator=(SoundProxy&& proxy) noexcept
{
    position_[0] = proxy.position_[0];
    position_[1] = proxy.position_[1];
    position_[2] = proxy.position_[2];
    velocity_[0] = proxy.velocity_[0];
    velocity_[1] = proxy.velocity_[1];
    velocity_[2] = proxy.velocity_[2];
    system_ = std::move(proxy.system_);
    sounds_ = std::move(proxy.sounds_);
    return *this;
}

void SoundProxy::SetPosition(float px, float py, float pz)
{
    position_[0] = px;
    position_[1] = py;
    position_[2] = pz;
    for (auto& sound : sounds_)
        alSource3f(sound.second.source, AL_POSITION, px, py, pz);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::SetVelocity(float vx, float vy, float vz)
{
    velocity_[0] = vx;
    velocity_[1] = vy;
    velocity_[2] = vz;
    for (auto& sound : sounds_)
        alSource3f(sound.second.source, AL_VELOCITY, vx, vy, vz);

    assert(alGetError() == AL_NO_ERROR);
}

std::array<float, 3> SoundProxy::GetPosition() const
{
    return { position_[0], position_[1], position_[2] };
}

std::array<float, 3> SoundProxy::GetVelocity() const
{
    return { velocity_[0], velocity_[1], velocity_[2] };
}

void SoundProxy::PlaySound(const std::string& soundName, float duration)
{
    if (sounds_.find(soundName) == std::end(sounds_))
    {
        auto buffer = system_->GetSoundBuffer(soundName);
        ALuint source = 0;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        sounds_[soundName] = { duration, 0.0f, source };
    }

    auto sound = sounds_[soundName];
    sound.duration = duration;
    sound.time = 0.0f;
    alSource3f(sound.source, AL_POSITION, position_[0], position_[1], position_[2]);
    alSource3f(sound.source, AL_VELOCITY, velocity_[0], velocity_[1], velocity_[2]);
    alSourcePlay(sound.source);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::PauseSound(const std::string& soundName)
{
    alSourcePause(sounds_[soundName].source);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::StopSound(const std::string& soundName)
{
    alSourceStop(sounds_[soundName].source);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::StopAllSounds()
{
    for (auto& sound : sounds_)
        alSourceStop(sound.second.source);

    assert(alGetError() == AL_NO_ERROR);
}

SoundState SoundProxy::GetSoundState(const std::string& soundName) const
{
    ALint state;
    auto sound = sounds_.find(soundName);
    alGetSourcei(sound->second.source, AL_SOURCE_STATE, &state);

    assert(alGetError() == AL_NO_ERROR);

    switch (state)
    {
    case AL_INITIAL:
        return SoundState::Initial;
    case AL_PLAYING:
        return SoundState::Playing;
    case AL_PAUSED:
        return SoundState::Paused;
    case AL_STOPPED:
        return SoundState::Stopped;
    default:
        return SoundState::Unknown;
    }
}

void SoundProxy::SetSoundLoop(const std::string& soundName, bool loop)
{
    alSourcei(sounds_[soundName].source, AL_LOOPING, loop);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::SetSoundGain(const std::string& soundName, float gain)
{
    alSourcef(sounds_[soundName].source, AL_GAIN, gain);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::Update(float dt)
{
    for (auto& sound : sounds_)
    {
        ALint state;
        alGetSourcei(sound.second.source, AL_SOURCE_STATE, &state);
        if (state != AL_STOPPED && sound.second.duration != 0.0f)
        {
            sound.second.time += dt;
            if (sound.second.time > sound.second.duration)
                alSourceStop(sound.second.source);
        }
    }
}

SoundProxy::~SoundProxy()
{
    for (auto& sound : sounds_)
        alDeleteSources(1, &sound.second.source);
}
