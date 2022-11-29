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
<<<<<<< HEAD
  class ISoundSystem* ptr;
=======
  class SoundSystem* ptr;
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
};

struct SoundProxyPtr
{
<<<<<<< HEAD
  std::unique_ptr<class ISoundProxy> ptr;
=======
  std::unique_ptr<class SoundProxy> ptr;
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4
};

struct DestroyTimer { float time; float acc = 0; };

struct Creatable {};
