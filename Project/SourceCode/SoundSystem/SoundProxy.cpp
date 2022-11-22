#include "pch.h"
#include <cassert>
#include "SoundProxy.h"
#include "SoundSystem.h"
#include <array>

SoundProxy::SoundProxy(SoundProxy&& proxy) noexcept :
    system_(std::move(proxy.system_)),
    sources_(std::move(proxy.sources_))
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
    sources_ = std::move(proxy.sources_);
    return *this;
}

void SoundProxy::SetPosition(float px, float py, float pz)
{
    position_[0] = px;
    position_[1] = py;
    position_[2] = pz;
    for (auto& source : sources_)
        alSource3f(source.second, AL_POSITION, px, py, pz);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::SetVelocity(float vx, float vy, float vz)
{
    velocity_[0] = vx;
    velocity_[1] = vy;
    velocity_[2] = vz;
    for (auto& source : sources_)
        alSource3f(source.second, AL_VELOCITY, vx, vy, vz);

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

void SoundProxy::PlaySound(const std::string& soundName)
{
    if (sources_.find(soundName) == std::end(sources_))
    {
        auto buffer = system_->GetSoundBuffer(soundName);
        ALuint source = 0;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        sources_[soundName] = source;
    }

    auto source = sources_[soundName];
    alSource3f(source, AL_POSITION, position_[0], position_[1], position_[2]);
    alSource3f(source, AL_VELOCITY, velocity_[0], velocity_[1], velocity_[2]);
    alSourcePlay(source);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::PauseSound(const std::string& soundName)
{
    alSourcePause(sources_[soundName]);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::StopSound(const std::string& soundName)
{
    alSourceStop(sources_[soundName]);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::StopAllSounds()
{
    for (auto& source : sources_)
        alSourceStop(source.second);

    assert(alGetError() == AL_NO_ERROR);
}

SoundState SoundProxy::GetSoundState(const std::string& soundName) const
{
    ALint state;
    auto source = sources_.find(soundName);
    alGetSourcei(source->second, AL_SOURCE_STATE, &state);

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
    alSourcei(sources_[soundName], AL_LOOPING, loop);

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::SetSoundGain(const std::string& soundName, float gain)
{
    alSourcef(sources_[soundName], AL_GAIN, gain);

    assert(alGetError() == AL_NO_ERROR);
}

SoundProxy::~SoundProxy()
{
    for (auto& source : sources_)
        alDeleteSources(1, &source.second);
}
