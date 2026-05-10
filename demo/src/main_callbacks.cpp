/*
 * Demo with callbacks
 */
#include "RayFlux/Main.h"
#include "RayFlux/Gui.h"

#include "Lights.h"
#include "Eyes.h"
//------------------------------------------------------------------------------
using namespace RayFlux::Tools;
//------------------------------------------------------------------------------
int main(void)
{
    RayFlux::Main app;
    app.getSettings()->WindowMaximized = true;
    app.getSettings()->IconFilename = "texture:/raylib_32x32.png";
    // app.settings.FullScreen = true;

    if (!app.Init()) {
        TraceLog(LOG_ERROR, "%s", "Failed to Initialize!");
        return 1;
    }

    RayFlux::Demo::Eyes Eyes;
    Eyes.Init();

    RayFlux::Demo::Lights Lights;
    Lights.Init();

    // Music
    app.playMusic("fullhouse2026.fms.mp3", 0.75f);

    // Texture
    Texture2D *logoTex = app.getResourceManager()->getTexture("raylib_32x32.png");

    //-------
    std::string confPathText = TextFormat("Base Path: %s", getBasePath().c_str());
    std::string prefPathText = TextFormat("Config Path: %s", app.getSettings()->getPrefsPath().c_str());
    RayFlux::LazyGui lg {10, 10, 20};

    //------
    app.OnUpdate = [&](F32 dt) {
        Eyes.Update(dt);
        Lights.Update(dt);
    };
    //------
    app.OnRender = [&]() {

        Lights.Render3D();
        Eyes.Render();
        lg.y = 10;

        // logo
        if (logoTex) DrawTexture(*logoTex, lg.x, lg.x, WHITE);
        lg.y += 40.f;
        lg.size = 40;
        lg.Write("RayLib Test .....", GOLD);
        lg.size = 20;
        lg.Write(TextFormat("FPS: %d", GetFPS()),  RED);
        lg.size = 10;
        lg.Write(confPathText.c_str(), ORANGE);
        lg.Write(prefPathText.c_str(), SKYBLUE);
        lg.Write(logoTex ? "Logo loaded" : "Logo failed!");
        lg.size = 20;
        lg.Write("LIGHTS:", WHITE);
        Lights.RenderGui(lg);


        if (lg.Button(100.f, "Test Sound" ) == 1) {
            app.playSound("flee.mp3");
        }
    };
    //--------
    app.OnShutDown = [&]() {
       Lights.ShutDown();
    };
    //--------
    app.Execute();

    return 0;
}
