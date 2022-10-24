#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "RenderThread.h"
#include "RenderEngine.h"
#include "CubeRenderProxy.h"

void register_ecs_mesh_systems(flecs::world &ecs)
{
  static auto renderQuery = ecs.query<RenderEnginePtr, CubeMeshes>();
  ecs.system<const CubeMesh>()
    .each([&](flecs::entity e, const CubeMesh& cubeMesh)
    {
      renderQuery.each([&](RenderEnginePtr re, CubeMeshes &meshes)
      {
          RenderProxy* renderProxy = nullptr;
          for (auto mesh : meshes.container)
          {
            if (!mesh->IsRenderable())
            {
              renderProxy = mesh;
              break;
            }
          }
          if (!renderProxy)
          {
              renderProxy = new CubeRenderProxy;
              re.ptr->GetRT()->EnqueueCommand(RC_CreateCubeRenderObject, renderProxy);
              meshes.container.push_back(renderProxy);
          }
          float position[3];
          position[0] = -100.0f;
          position[1] = -100.0f;
          position[2] = -100.0f;

          renderProxy->SetPosition(position);
          renderProxy->SetRenderable(true);
          e.set(RenderProxyPtr{ renderProxy });
          e.remove<CubeMesh>();
      });
    });

  ecs.system<RenderProxyPtr, const Position>()
    .each([&](RenderProxyPtr &renderProxy, const Position &pos)
    {
      renderQuery.each([&](RenderEnginePtr re, CubeMeshes&)
      {
           float position[3];
           position[0] = pos.x;
           position[1] = pos.y;
           position[2] = pos.z;

           renderProxy.ptr->SetPosition(position);
      });
    });

  ecs.system<RenderProxyPtr, const Scale>()
    .each([&](RenderProxyPtr &renderProxy, const Scale &s)
    {
      renderQuery.each([&](RenderEnginePtr re, CubeMeshes&)
      {
           renderProxy.ptr->SetScale(s.val);
      });
    });
}

