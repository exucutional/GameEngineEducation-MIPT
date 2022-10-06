#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../InputHandler.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler);

	void Update();
private:
	int creatableMaxCount;
	flecs::world ecs;
};

