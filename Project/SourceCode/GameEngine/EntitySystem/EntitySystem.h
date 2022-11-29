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
<<<<<<< HEAD
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, ISoundSystem* soundSystem);
=======
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, SoundSystem* soundSystem);
>>>>>>> 587b67b690f3376290d53ce9a6470639dba39ec4

	void Update();
	void CreateEntities();
private:
	int creatableMaxCount;
	flecs::world ecs;
};

