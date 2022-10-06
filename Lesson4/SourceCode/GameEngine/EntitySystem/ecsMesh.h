#pragma once
#include <vector>
#include "flecs.h"

struct Scale { float val; };

struct CubeMesh {};

struct RenderProxyPtr
{
	class RenderProxy* ptr;
};

struct CubeMeshes
{
	std::vector<RenderProxy*> container;
};

void register_ecs_mesh_systems(flecs::world &ecs);

