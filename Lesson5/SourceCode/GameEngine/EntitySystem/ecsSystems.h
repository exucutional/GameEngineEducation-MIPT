#pragma once

struct InputHandlerPtr
{
  class InputHandler* ptr;
};

struct RenderEnginePtr
{
  class RenderEngine* ptr;
};

struct DestroyTimer { float time; float acc = 0; };

struct Creatable {};
