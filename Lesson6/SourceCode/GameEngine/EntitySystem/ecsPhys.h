#pragma once
#include "flecs.h"

struct Position
{
	float x, y, z;
};

struct Velocity
{
	float x, y, z;
};

struct Gravity
{
	float x, y, z;
};

struct BouncePlane
{
  float x,y,z,w;
};

struct Bounciness
{
  float val;
};

struct ShiverAmount
{
  float val;
};

struct FrictionAmount
{
  float val;
};

struct BoundingBox
{
  float x, y, z;
};

struct DestroyPlane
{
  float x, y, z, w, time;
};

typedef float Speed;

void register_ecs_phys_systems(flecs::world &ecs);
