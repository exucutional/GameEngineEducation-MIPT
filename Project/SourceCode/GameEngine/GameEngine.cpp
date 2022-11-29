// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "GameTimer.h"
#include "InputHandler.h"
#include "EntitySystem/EntitySystem.h"
#include "../ScriptSystem/ScriptSystem.h"
#include "SoundSystem.h"


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
    IScriptSystem* scriptSystem = new CScriptSystem();
    ISoundSystem* soundSystem = new SoundSystem();
    LoadAudio(soundSystem);
    auto backgroundSound = soundSystem->CreateProxy();
    backgroundSound->PlaySound("sound-background");
    backgroundSound->SetSoundGain("sound-background", 0.1f);
    backgroundSound->SetSoundLoop("sound-background", true);
    EntitySystem* entitySystem = new EntitySystem(renderEngine, inputHandler, scriptSystem, soundSystem);

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
            entitySystem->Update();
            scriptSystem->Update(timer.DeltaTime());

            timer.Tick();

            renderThread->OnEndFrame();
        }
    }

    delete renderEngine;
    delete inputHandler;
    delete scriptSystem;
    delete soundSystem;
    return (int) msg.wParam;
}

void LoadAudio(ISoundSystem* system)
{
    system->LoadSound("../../../Assets/Audio/laser6.wav", "sound-shoot");
    system->LoadSound("../../../Assets/Audio/mixkit-game-level-music-689.wav", "sound-background");
    system->LoadSound("../../../Assets/Audio/mixkit-quick-jump-arcade-game-239.wav", "sound-jump");
}
