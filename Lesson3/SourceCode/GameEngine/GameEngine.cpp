// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include<random>
#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "InputHandler.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();

    //GameObject* cube = new CubeGameObject();
    //renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
    auto cubes = std::vector<std::unique_ptr<CubeGameObject>>();
    const int row = 10;
    const int col = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 2);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cubes.emplace_back(std::make_unique<CubeGameObject>());
            auto& cube = cubes.back();
            renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
            cube->SetPosition(3.5f * (j - row / 2), 0.0f, 3.5f * i);
            cube->SetVelocity(0.0f, 0.0f, 0.0f);
            int randInt = distrib(gen);
            switch (randInt)
            {
            case 0:
                cube->setType(CubeGameObject::BehavType::FrontBackMove);
                break;
            case 1:
                cube->setType(CubeGameObject::BehavType::LeftRightControl);
                break;
            default:
                cube->setType(CubeGameObject::BehavType::UpJump);
                break;
            }
        }
    }
    MSG msg = { 0 };

    timer.Start();
    timer.Reset();


    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            inputHandler->Update();

            float t = 0;
            timer.Tick();
            t = sin(timer.TotalTime())*2;
            for (auto& cube : cubes)
            {
                Vector3d pos = cube->GetPosition();
                Vector3d vel = cube->GetVelocity();
                switch (cube->getType())
                {
                case CubeGameObject::BehavType::FrontBackMove:
                    cube->SetVelocity(0.0f, 0.0f, t);
                    break;
                case CubeGameObject::BehavType::LeftRightControl:
                    cube->SetVelocity(0.0f, 0.0f, 0.0f);
                    if (inputHandler->GetInputState().test(eIC_GoLeft))
                        cube->SetVelocity(-1.0f, 0.0f, 0.0f);
                    if (inputHandler->GetInputState().test(eIC_GoRight))
                        cube->SetVelocity(1.0f, 0.0f, 0.0f);
                    break;
                case CubeGameObject::BehavType::UpJump:
                    if (pos.y > 0)
                        cube->SetVelocity(0.0f, vel.y - 9.81 * timer.DeltaTime(), 0.0f);
                    else
                        cube->SetVelocity(0.0f, 9.81f, 0.0f);
                    break;
                default:
                    break;
                }
                vel = cube->GetVelocity();
                float delta = timer.DeltaTime();
                cube->SetPosition(
                    pos.x + vel.x * delta,
                    pos.y + vel.y * delta,
                    pos.z + vel.z * delta);
            }
            //newPositionX += velocity * timer.DeltaTime();
            //cube->SetPosition(newPositionX, 0.0f, 0.0f);

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
