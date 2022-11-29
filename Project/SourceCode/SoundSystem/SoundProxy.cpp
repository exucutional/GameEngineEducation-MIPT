#include "pch.h"
#include <cassert>
#include "SoundProxy.h"
#include "SoundSystem.h"
#include <array>

SoundProxy::SoundProxy(SoundProxy&& proxy) noexcept :
    system_(std::move(proxy.system_)),
<<<<<<< HEAD
    sounds_(std::move(proxy.sounds_))
=======
    sources_(std::move(proxy.sources_))
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
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
<<<<<<< HEAD
    sounds_ = std::move(proxy.sounds_);
=======
    sources_ = std::move(proxy.sources_);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
    return *this;
}

void SoundProxy::SetPosition(float px, float py, float pz)
{
    position_[0] = px;
    position_[1] = py;
    position_[2] = pz;
<<<<<<< HEAD
    for (auto& sound : sounds_)
        alSource3f(sound.second.source, AL_POSITION, px, py, pz);
=======
    for (auto& source : sources_)
        alSource3f(source.second, AL_POSITION, px, py, pz);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::SetVelocity(float vx, float vy, float vz)
{
    velocity_[0] = vx;
    velocity_[1] = vy;
    velocity_[2] = vz;
<<<<<<< HEAD
    for (auto& sound : sounds_)
        alSource3f(sound.second.source, AL_VELOCITY, vx, vy, vz);
=======
    for (auto& source : sources_)
        alSource3f(source.second, AL_VELOCITY, vx, vy, vz);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

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

<<<<<<< HEAD
void SoundProxy::PlaySound(const std::string& soundName, float duration)
{
    if (sounds_.find(soundName) == std::end(sounds_))
=======
void SoundProxy::PlaySound(const std::string& soundName)
{
    if (sources_.find(soundName) == std::end(sources_))
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
    {
        auto buffer = system_->GetSoundBuffer(soundName);
        ALuint source = 0;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
<<<<<<< HEAD
        sounds_[soundName] = { duration, 0.0f, source };
    }

    auto sound = sounds_[soundName];
    sound.duration = duration;
    sound.time = 0.0f;
    alSource3f(sound.source, AL_POSITION, position_[0], position_[1], position_[2]);
    alSource3f(sound.source, AL_VELOCITY, velocity_[0], velocity_[1], velocity_[2]);
    alSourcePlay(sound.source);
=======
        sources_[soundName] = source;
    }

    auto source = sources_[soundName];
    alSource3f(source, AL_POSITION, position_[0], position_[1], position_[2]);
    alSource3f(source, AL_VELOCITY, velocity_[0], velocity_[1], velocity_[2]);
    alSourcePlay(source);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::PauseSound(const std::string& soundName)
{
<<<<<<< HEAD
    alSourcePause(sounds_[soundName].source);
=======
    alSourcePause(sources_[soundName]);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::StopSound(const std::string& soundName)
{
<<<<<<< HEAD
    alSourceStop(sounds_[soundName].source);
=======
    alSourceStop(sources_[soundName]);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::StopAllSounds()
{
<<<<<<< HEAD
    for (auto& sound : sounds_)
        alSourceStop(sound.second.source);
=======
    for (auto& source : sources_)
        alSourceStop(source.second);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

SoundState SoundProxy::GetSoundState(const std::string& soundName) const
{
    ALint state;
<<<<<<< HEAD
    auto sound = sounds_.find(soundName);
    alGetSourcei(sound->second.source, AL_SOURCE_STATE, &state);
=======
    auto source = sources_.find(soundName);
    alGetSourcei(source->second, AL_SOURCE_STATE, &state);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

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
<<<<<<< HEAD
    alSourcei(sounds_[soundName].source, AL_LOOPING, loop);
=======
    alSourcei(sources_[soundName], AL_LOOPING, loop);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

void SoundProxy::SetSoundGain(const std::string& soundName, float gain)
{
<<<<<<< HEAD
    alSourcef(sounds_[soundName].source, AL_GAIN, gain);
=======
    alSourcef(sources_[soundName], AL_GAIN, gain);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

    assert(alGetError() == AL_NO_ERROR);
}

<<<<<<< HEAD
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
=======
SoundProxy::~SoundProxy()
{
    for (auto& source : sources_)
        alDeleteSources(1, &source.second);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
}
