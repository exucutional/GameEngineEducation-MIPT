#pragma once

#include <memory>

struct InputHandlerPtr
{
  class InputHandler* ptr;
};

struct RenderEnginePtr
{
  class RenderEngine* ptr;
};

struct ScriptSystemPtr
{
  class IScriptSystem* ptr;
};

struct SoundSystemPtr
{
  class ISoundSystem* ptr;
};

struct SoundProxyPtr
{
  std::unique_ptr<class ISoundProxy> ptr;
};

struct DestroyTimer { float time; float acc = 0; };

struct Creatable {};
