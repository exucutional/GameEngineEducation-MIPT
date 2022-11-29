#include "pch.h"
#include <cassert>
#include <array>
#include "SoundSystem.h"

SoundSystem::SoundSystem(const char* deviceName)
{
    device_ = alcOpenDevice(deviceName);
    if (!device_)
        throw std::runtime_error("Couldn't open audio device");

    context_ = alcCreateContext(device_, nullptr);
    if (!context_)
    {
        alcCloseDevice(device_);
        throw std::runtime_error("Couldn't create audio context");
    }
    alcMakeContextCurrent(context_);
    assert(alGetError() == AL_NO_ERROR);
}

void SoundSystem::LoadSound(const std::string& fileName, const std::string& soundName)
{
    SF_INFO sfinfo;
    auto sndfile = sf_open(fileName.c_str(), SFM_READ, &sfinfo);
    if (!sndfile)
    {
        sf_close(sndfile);
        throw std::runtime_error("Couldn't open audio file: " + fileName);
    }

    ALenum format = AL_NONE;
    switch (sfinfo.channels)
    {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    default:
        sf_close(sndfile);
        throw std::runtime_error("Unsupported channel count: " + sfinfo.channels);
    }

    short* memPtr = (short*)malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short));

    auto numFrames = sf_readf_short(sndfile, memPtr, sfinfo.frames);
    if (numFrames < 1)
    {
        free(memPtr);
        sf_close(sndfile);
        throw std::runtime_error("Couldn't read frames in: " + fileName);
    }

    ALsizei numBytes = (ALsizei)(numFrames * sfinfo.channels) * (ALsizei)sizeof(short);

    ALuint buffer = 0u;
    alGenBuffers(1, &buffer);
    assert(alGetError() == AL_NO_ERROR);
    alBufferData(buffer, format, memPtr, numBytes, sfinfo.samplerate);
    assert(alGetError() == AL_NO_ERROR);
    free(memPtr);
    sf_close(sndfile);
    buffers_[soundName] = buffer;
}

void SoundSystem::UnloadSound(const std::string& soundName)
{
    auto bufferIter = buffers_.find(soundName);
    if (bufferIter != std::end(buffers_))
    {
        alDeleteBuffers(1, &bufferIter->second);
        buffers_.erase(bufferIter);
    }
}

std::unique_ptr<ISoundProxy> SoundSystem::CreateProxy()
{
    return std::make_unique<SoundProxy>(this);
}

ALuint SoundSystem::GetSoundBuffer(const std::string& soundName) const
{
    auto bufferIter = buffers_.find(soundName);
    if (bufferIter == std::end(buffers_))
        throw std::runtime_error(soundName + " is not loaded");

    return bufferIter->second;
}

void SoundSystem::SetListenerPosition(float px, float py, float pz)
{
    alListener3f(AL_POSITION, px, py, pz);
    assert(alGetError() == AL_NO_ERROR);
}

void SoundSystem::SetListenerVelocity(float vx, float vy, float vz)
{
    alListener3f(AL_VELOCITY, vx, vy, vz);
    assert(alGetError() == AL_NO_ERROR);
}

std::array<float, 3> SoundSystem::GetListenerPosition() const
{
    float px, py, pz;
    alGetListener3f(AL_POSITION, &px, &py, &pz);
    assert(alGetError() == AL_NO_ERROR);
    return { px, py, pz };
}

std::array<float, 3> SoundSystem::GetListenerVelocity() const
{
    float vx, vy, vz;
    alGetListener3f(AL_POSITION, &vx, &vy, &vz);
    assert(alGetError() == AL_NO_ERROR);
    return { vx, vy, vz };
}

SoundSystem::~SoundSystem()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context_);
    alcCloseDevice(device_);
    for (auto& buffer : buffers_)
        alDeleteBuffers(1, &buffer.second);
}
