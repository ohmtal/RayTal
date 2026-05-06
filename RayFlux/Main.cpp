#include "Main.h"

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

        return true;
    }
    //----------------------------------------------------------------------
    void Main::Execute() {
        while (!WindowShouldClose())
        {
            // fixme fixed update / deltaTime
            if (OnUpdate) OnUpdate(0.166);

            BeginDrawing();
            ClearBackground(COLOR_SLATEGRAY);
            if (OnRender) OnRender();
            EndDrawing();
        }
        if (OnShutDown) OnShutDown();
        CloseWindow();
    }

}

