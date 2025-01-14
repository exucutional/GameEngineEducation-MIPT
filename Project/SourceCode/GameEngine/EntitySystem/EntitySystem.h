#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../InputHandler.h"
#include "SoundSystem.h"

class IScriptSystem;

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, ISoundSystem* soundSystem);

	void Update();
	void CreateEntities();
private:
	int creatableMaxCount;
	flecs::world ecs;
};

