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
  class SoundSystem* ptr;
};

struct SoundProxyPtr
{
  std::unique_ptr<class SoundProxy> ptr;
};

struct DestroyTimer { float time; float acc = 0; };

struct Creatable {};
