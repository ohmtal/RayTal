#include "Main.h"
#include "ResourceManager.h"

namespace RayFlux {
    //----------------------------------------------------------------------

    bool Main::Init() {
        int windowFlags = 0;
        if (mSettings.windowFlagsOverwrite) windowFlags = mSettings.windowFlagsOverwrite;
        else {
            if (mSettings.FullScreen) windowFlags |=  FLAG_FULLSCREEN_MODE;
            else {
                windowFlags |= FLAG_WINDOW_RESIZABLE;
                if (mSettings.WindowMaximized) windowFlags |= FLAG_WINDOW_MAXIMIZED;
            }
            if (mSettings.EnableVSync) windowFlags |= FLAG_VSYNC_HINT;
            if (mSettings.EnableFSAA) windowFlags |= FLAG_MSAA_4X_HINT;
        }

        SetConfigFlags(windowFlags);
        if (mSettings.FpsLimit) SetTargetFPS(mSettings.FpsLimit);
        InitWindow(mSettings.ScreenWidth, mSettings.ScreenHeight, mSettings.Caption.c_str());
        if (!IsWindowReady()) return false;

        setFullPath( getSettings()->IconFilename );

        Image imgLogo = LoadImage( getSettings()->IconFilename.c_str() );
        SetWindowIcon(imgLogo);
        // can i unload ?  - seams so
        UnloadImage(imgLogo);

        mResourceManager = std::make_unique<ResourceManager>(this);

        if (!getSettings()->DisableSound) {
            InitAudioDevice();
        }

        return true;
    }
    //----------------------------------------------------------------------
    void Main::ShutDown() {
        mResourceManager->shutDown();
    }
    //----------------------------------------------------------------------
    void Main::Execute() {
        F32 deltaTime = 0.1666f;
        const F32 fixedStep = 1.0f / 60.0f;
        static F32 accumulator = 0.0f;


        while (!WindowShouldClose())
        {

            accumulator += GetFrameTime();
            while (accumulator >= fixedStep) {

                if (OnUpdate) OnUpdate(fixedStep);
                mResourceManager->Update();

                accumulator -= fixedStep;
            }


            BeginDrawing();
            ClearBackground(COLOR_SLATEGRAY);
            if (OnRender) OnRender();
            EndDrawing();
        }
        if (OnShutDown) OnShutDown();
        ShutDown();
        CloseWindow();
    }
    //----------------------------------------------------------------------

}

