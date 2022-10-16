#include "ecsPhys.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsSystems.h"
#include "CubeRenderProxy.h"
#include <stdlib.h>

static float rand_flt(float from, float to)
{
  return from + (float(rand()) / RAND_MAX) * (to - from);
}

static bool is_box_intersected(const Position& pos, const BoundingBox& box, const Position& other_pos, const BoundingBox& other_box)
{
  return (abs(pos.x - other_pos.x) < (box.x + other_box.x))
    && (abs(pos.y - other_pos.y) < (box.y + other_box.y))
    && (abs(pos.z - other_pos.z) < (box.z + other_box.z));
}

void register_ecs_phys_systems(flecs::world &ecs)
{
  static auto boundingQuery = ecs.query<const Position, const BoundingBox, const Enemy, const MagBonus*,
    RenderProxyPtr*, Respawnable*>();
  static auto shootableQuery = ecs.query<Shootable>();
  static auto creatableQuery = ecs.query<Creatable>();

  ecs.system<Velocity, const Gravity, BouncePlane*, Position*>()
    .each([&](flecs::entity e, Velocity &vel, const Gravity &grav,
      BouncePlane *plane, Position *pos)
    {
      if (plane && pos)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane->x * pos->x + plane->y * pos->y + plane->z * pos->z < plane->w + planeEpsilon)
          return;
      }
      vel.x += grav.x * e.delta_time();
      vel.y += grav.y * e.delta_time();
      vel.z += grav.z * e.delta_time();
    });

  ecs.system<const Position, const DestroyPlane, DestroyTimer*>()
    .each([&](flecs::entity e, const Position &pos, const DestroyPlane &plane, DestroyTimer *timer)
    {
      float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
      if (dotPos < plane.w && !timer)
        e.set(DestroyTimer{ plane.time });

    });

  ecs.system<Velocity, Position, const BouncePlane, const Bounciness>()
    .each([&](Velocity &vel, Position &pos, const BouncePlane &plane, const Bounciness &bounciness)
    {
      float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
      float dotVel = plane.x * vel.x + plane.y * vel.y + plane.z * vel.z;
      if (dotPos < plane.w)
      {
        pos.x -= (dotPos - plane.w) * plane.x;
        pos.y -= (dotPos - plane.w) * plane.y;
        pos.z -= (dotPos - plane.w) * plane.z;

        vel.x -= (1.f + bounciness.val) * plane.x * dotVel;
        vel.y -= (1.f + bounciness.val) * plane.y * dotVel;
        vel.z -= (1.f + bounciness.val) * plane.z * dotVel;
      }
    });

  ecs.system<Velocity, const FrictionAmount>()
    .each([&](flecs::entity e, Velocity &vel, const FrictionAmount &friction)
    {
      vel.x -= vel.x * friction.val * e.delta_time();
      vel.y -= vel.y * friction.val * e.delta_time();
      vel.z -= vel.z * friction.val * e.delta_time();
    });


  ecs.system<Position, const Velocity>()
    .each([&](flecs::entity e, Position &pos, const Velocity &vel)
    {
      pos.x += vel.x * e.delta_time();
      pos.y += vel.y * e.delta_time();
      pos.z += vel.z * e.delta_time();
    });


  ecs.system<Position, const ShiverAmount>()
    .each([&](flecs::entity e, Position &pos, const ShiverAmount &shiver)
    {
      pos.x += rand_flt(-shiver.val, shiver.val);
      pos.y += rand_flt(-shiver.val, shiver.val);
      pos.z += rand_flt(-shiver.val, shiver.val);
    });

  ecs.system<const Position, const BoundingBox, const Projectile, RenderProxyPtr*>()
    .each([&](flecs::entity e, const Position &pos, const BoundingBox &box, const Projectile &, RenderProxyPtr *renderProxy)
    {
      bool self_destruct = false;
      boundingQuery.each(
        [&](flecs::entity otherE, const Position &otherPos, const BoundingBox &otherBox,
            const Enemy &enemy, const MagBonus *magBonus, RenderProxyPtr *otherRenderProxy, Respawnable *respawn)
        {
          if (e.id() != otherE.id() && is_box_intersected(pos, box, otherPos, otherBox))
          {
            if (otherRenderProxy)
                otherRenderProxy->ptr->SetRenderable(false);

            if (magBonus)
                shootableQuery.each([&](Shootable &shoot) { shoot.mag += magBonus->val; });

            if (respawn)
            {
              int toCreate = 1;
              int created = 0;
              creatableQuery
                .each([&](flecs::entity eNew, Creatable &)
                {
                  if (created++ < toCreate)
                    eNew.mut(e)
                      .set(Position{ otherPos.x, 0.0f, otherPos.z })
                      .set(RespawnTimer{ respawn->e, 5.0f })
                      .remove<Creatable>();
                });
            }
            otherE.mut(e).destruct();
            self_destruct = true;
          }
        });
      if (self_destruct)
      {
        if (renderProxy)
            renderProxy->ptr->SetRenderable(false);

        e.destruct();
      }
    });

  ecs.system<DestroyTimer, RenderProxyPtr*>()
    .each([&](flecs::entity e, DestroyTimer &timer, RenderProxyPtr *renderProxy)
    {
      timer.acc += ecs.delta_time();
      if (timer.acc > timer.time)
      {
        if (renderProxy)
          renderProxy->ptr->SetRenderable(false);

        e.destruct();
      }
    });

  ecs.system<RespawnTimer>()
    .each([&](flecs::entity e, RespawnTimer &timer)
    {
      timer.acc += ecs.delta_time();
      if (timer.acc > timer.time)
          e.is_a(timer.e)
            .add<CubeMesh>()
            .set(Respawnable{ timer.e })
            .remove<RespawnTimer>();
    });
}

