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
    app.getSettings()->EnableVSync = false;
    app.getSettings()->setFPSLimit(500);
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
    Music* mainMusic = app.getMusic("fullhouse2026.fms.mp3");
    if (mainMusic) {
        SetMusicVolume(*mainMusic, 0.75);
        PlayMusicStream(*mainMusic);
    }
    // app.playMusic("fullhouse2026.fms.mp3", 0.75f);

    // Texture
    Texture2D *logoTex = app.getResourceManager()->getTexture("raylib_32x32.png");

    //-------
    std::string confPathText = TextFormat("Base Path: %s", getBasePath().c_str());
    std::string prefPathText = TextFormat("Config Path: %s", app.getSettings()->getPrefsPath().c_str());
    RayFlux::LazyGui lg {10.f, 10.f};

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
        lg.size = 40.f;
        if (logoTex) DrawTexture(*logoTex, lg.x, lg.x, WHITE);
        lg.x += 40.f;
        lg.Write("RayFlux Demo", GOLD);
        lg.x = 10.f;
        lg.size = 20;
        lg.Write(TextFormat("FPS: %d", GetFPS()),  RED);
        lg.size = 10;
        lg.Write(confPathText.c_str(), ORANGE);
        lg.Write(prefPathText.c_str(), SKYBLUE);
        lg.Write(logoTex ? "Logo loaded" : "Logo failed!");

        lg.size = 16;

        lg.size = 20;
        lg.CheckBox("Light Demo enabled", &Lights.isEnabled);
        Lights.RenderGui(lg);

        lg.Separator(100.f);
        if (mainMusic) {
            bool isMusicPlaying = IsMusicStreamPlaying(*mainMusic);
            if (lg.CheckBox("Music", &isMusicPlaying)) {
                // resume cant be used if not play was called before !
                if (!isMusicPlaying) PauseMusicStream(*mainMusic);
                else ResumeMusicStream(*mainMusic);
            }
        }
        if (lg.Button(100.f, "Test Sound" ) == 1) {
            app.playSound("flee.mp3");
        }
        lg.Separator(100.f);
        if (lg.CheckBox("VSnyc", &app.getSettings()->EnableVSync)) {
            app.getSettings()->setVSync(app.getSettings()->EnableVSync);
        }
        if (lg.CheckBox("FullScreen", &app.getSettings()->FullScreen)) {
            app.getSettings()->setFullScreen(app.getSettings()->FullScreen);
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
