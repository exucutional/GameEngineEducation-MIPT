#pragma once
#include "flecs.h"

struct Controllable {};

struct JumpSpeed { float val; };

struct Shootable { flecs::entity projectile; int mag; };

struct MagBonus { int val; };

struct Projectile {};

struct ReloadTimer { int mag; float time; float acc = 0; };

struct RespawnTimer { flecs::entity e; float time; float acc = 0; };

struct Enemy {};

struct Respawnable { flecs::entity e; };

void register_ecs_control_systems(flecs::world &ecs);

