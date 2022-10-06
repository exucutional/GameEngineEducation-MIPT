#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "RenderProxy.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();
  static auto creatableQuery = ecs.query<Creatable>();
  static bool shootPressed = false;
  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        float deltaVel[] = { 0.f, 0.0f, 0.0f };
        if (input.ptr->GetInputState().test(eIC_GoLeft))
          deltaVel[0] -= spd;
        if (input.ptr->GetInputState().test(eIC_GoRight))
          deltaVel[0] += spd;
        if (input.ptr->GetInputState().test(eIC_GoBackward))
          deltaVel[2] -= spd;
        if (input.ptr->GetInputState().test(eIC_GoForward))
          deltaVel[2] += spd;
        vel.x += deltaVel[0] * e.delta_time();
        vel.z += deltaVel[2] * e.delta_time();
      });
    });

  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump))
            vel.y = jump.val;
      });
    });

  ecs.system<const Position, const Velocity*,Shootable>()
    .each([&](flecs::entity e, const Position &pos, const Velocity *vel, Shootable &shoot)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        if (input.ptr->GetInputState().test(eIC_Shoot) && shoot.mag > 0)
        {
          if (!shootPressed)
          { 
            int toCreate = 1;
            int created = 0;
            creatableQuery.each([&](flecs::entity eNew, Creatable &)
            {
              if (created++ < toCreate)
              {
                float pVel[] = { 10.0f, 0.0f, 0.0f };
                if (vel)
                {
                    pVel[0] += vel->x;
                    pVel[1] += vel->y;
                    pVel[2] += vel->z;
                }
                eNew.mut(e)
                  .is_a(shoot.projectile)
                  .add<CubeMesh>()
                  .set(Position{ pos.x + 1.0f, pos.y, pos.z })
                  .set(Velocity{ pVel[0], pVel[1], pVel[2] })
                  .remove<Creatable>();
              }
            });
            shootPressed = true;
            shoot.mag--;
          }
        }
        else
        {
          shootPressed = false;
        }
      });
    });

  ecs.system<Shootable, ReloadTimer>()
    .each([&](flecs::entity e, Shootable &shoot, ReloadTimer &timer)
    {
      if (shoot.mag == 0)
        timer.acc += ecs.delta_time();

      if (timer.acc > timer.time)
      {
        shoot.mag += timer.mag;
        timer.acc = 0;
      }
    });
}

