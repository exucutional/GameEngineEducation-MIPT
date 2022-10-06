#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler):
    creatableMaxCount(30)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine })
        .set(CubeMeshes{});

    auto projectile = ecs.prefab()
        .set_override(Position{ 0.0f, 0.0f, 0.0f })
        .set_override(Velocity{ 0.0f, 0.0f, 0.0f })
        .set(BoundingBox{ 0.25f, 0.25f, 0.25f })
        .set(Scale{ 0.25f })
        .set(Bounciness{ 0.8f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, -5.0f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(FrictionAmount{ 0.7f })
        .set(DestroyPlane{ 0.f, 1.f, 0.f, -5.0f, 5.0f })
        .add<Projectile>();

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    for (int i = 0; i < creatableMaxCount; i++)
        ecs.entity().add<Creatable>();

    auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 2.0f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.3f })
        .set(Shootable{ projectile, 3 })
        .set(ReloadTimer{ 3, 2.0f })
        .add<Controllable>()
        .add<CubeMesh>();

    auto cubeEnemy = ecs.prefab()
        .set_override(Position{ 0.f, 0.f, 0.f })
        .set_override(Velocity{ 0.f, 0.f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, -5.0f })
        .set(Bounciness{ 1.0f })
        .set(BoundingBox{ 0.75f, 0.75f, 0.75f })
        .set(Scale{ 0.75f })
        .set(MagBonus{ 3 })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .add<Enemy>();

    int enemyCount = 5;
    for (int i = 0; i < enemyCount; i++)
    {
        ecs.entity()
            .is_a(cubeEnemy)
            .set(Position{ 5.0f, 0.0f, (-enemyCount / 2 + i) * 2.0f})
            .add<CubeMesh>()
            .set(Respawnable{ cubeEnemy });
    }
}

void EntitySystem::Update()
{
    static auto creatableQuery = ecs.query<Creatable>();
    ecs.progress();
    int creatableCount = 0;
    creatableQuery.each([&](Creatable&) { creatableCount += 1; });
    for (int i = creatableCount; i < creatableMaxCount; i++)
        ecs.entity().add<Creatable>();
}
