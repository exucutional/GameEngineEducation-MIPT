#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ecsScript.h"
#include "DataReader.h"
#include "SoundSystem.h"
#include <functional>
#include <array>

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, SoundSystem* soundSystem):
    creatableMaxCount(30)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine })
        .set(CubeMeshes{});
    ecs.entity("scriptSystem")
        .set(ScriptSystemPtr{ scriptSystem });
    ecs.entity("soundSystem")
        .set(SoundSystemPtr{ soundSystem });

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
    register_ecs_script_systems(ecs);

    for (int i = 0; i < creatableMaxCount; i++)
        ecs.entity().add<Creatable>();

    CreateEntities();

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

void EntitySystem::CreateEntities()
{
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
    std::unordered_map<std::string, std::function<void(flecs::entity, std::string)>> entityMap = {
        {"position", [](flecs::entity e, const std::string& params) {
            auto xyz = DataReader::StringToVec<3>(params);
            e.set(Position{ xyz[0], xyz[1], xyz[2] });
        }},
        {"velocity", [](flecs::entity e, const std::string& params) {
            auto xyz = DataReader::StringToVec<3>(params);
            e.set(Velocity{ xyz[0], xyz[1], xyz[2] });
        }},
        {"friction", [](flecs::entity e, const std::string& params) {
            auto value = std::stof(params);
            e.set(FrictionAmount{ value });
        }},
        {"gravity", [](flecs::entity e, const std::string& params) {
            auto xyz = DataReader::StringToVec<3>(params);
            e.set(Gravity{ xyz[0], xyz[1], xyz[2] });
        }},
        {"bounce_plane", [](flecs::entity e, const std::string& params) {
            auto xyzw = DataReader::StringToVec<4>(params);
            e.set(BouncePlane{ xyzw[0], xyzw[1], xyzw[2], xyzw[3] });
        }},
        {"bounciness", [](flecs::entity e, const std::string& params) {
            auto value = std::stof(params);
            e.set(Bounciness{ value });
        }},
        {"shootable", [projectile](flecs::entity e, const std::string& params) {
            auto value = std::stof(params);
            e.set(Shootable{ projectile, (int)value });
        }},
        {"reload_timer", [](flecs::entity e, const std::string& params) {
            auto xy = DataReader::StringToVec<2>(params);
            e.set(ReloadTimer{ (int)xy[0], xy[1] });
        }},
        {"script", [](flecs::entity e, const std::string& params) {
            auto scripts = e.get<Scripts>();
            if (scripts)
            {
                std::vector<std::string> names(scripts->names);
                names.push_back(params);
                e.set(Scripts{ names });
            }
            else
            {
                e.set(Scripts{ params });
            }
        }},
        {"cube_mesh", [](flecs::entity e, const std::string& params) {
            e.add<CubeMesh>();
        }},
        {"sound_proxy", [this](flecs::entity e, const std::string& params) {
            auto soundSystem = ecs.entity("soundSystem").get<SoundSystemPtr>();
            e.set(SoundProxyPtr{ soundSystem->ptr->CreateProxy() });
        }},
    };
    auto reader = DataReader();
    reader.LoadXMLFile("../../../Assets/Configs/entity.xml");
    auto entities = reader.GetEntities();
    for (auto& entity : entities)
    {
        auto e = ecs.entity();
        for (auto& component : entity)
            entityMap[component.first](e, component.second);
    }
}
