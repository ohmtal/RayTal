/*
 * Demo with callbacks
 */
#include "RayFlux/Main.h"
#include "RayFlux/Gui.h"


#include "Lights.h"
#include "Eyes.h"

#include "raygui_custom.h"

//FIXME write your one saver to FileHelper ?!
#define RINI_IMPLEMENTATION
#include "rini_custom.h"
#include "RayFlux/FileHelper.h"

#define Log(...) TraceLog(LOG_INFO, __VA_ARGS__);

//------------------------------------------------------------------------------
using namespace RayFlux::Tools;
std::string IniFileName = "pref://RayFlux.conf";
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
    F32 mainMusicVolume = 0.75f;
    if (mainMusic) {
        SetMusicVolume(*mainMusic, mainMusicVolume);

        // need to call play&pause else i can't use the CheckBox
        PlayMusicStream(*mainMusic);
        PauseMusicStream(*mainMusic);
    }

    // Texture
    Texture2D *logoTex = app.getResourceManager()->getTexture("raylib_32x32.png");

    //-------
    std::string confPathText = TextFormat("Base Path: %s", getBasePath().c_str());
    std::string prefPathText = TextFormat("Config Path: %s", app.getSettings()->getPrefsPath().c_str());
    // RayFlux::LazyGui lg {10.f, 10.f};
    RayFlux::Gui gui(10.f, 10.f);
    Vector2 defaultGuiSize{20.f, 20.f};

    //-------
    // FIXME SAVE/LOAD WEB CONFIG still not working !!!!!
    // FIXME write your own key/value handler KEY;VALUE[BASE64encoded]
    RayFlux::FileHelper::initFS(app.getSettings()->getPrefsPath().c_str()); //WEB
    app.getSettings()->setFullPath(IniFileName);
    TraceLog(LOG_INFO, ">>>>>>>>>>>>>>> IniFileName is: %s", IniFileName.c_str());
    rini_data config =  { 0 };

    if (!rini_load(config, IniFileName.c_str()))
        TraceLog(LOG_WARNING, ">>>>>>>>>>>>>>> Failed to open IniFile");


    const char* sponsors = rini_get_value_description(config, "SHOW_WINDOW_SPONSORS");
    if (sponsors) {
        TraceLog(LOG_INFO, ">>>>>>>>>>>>>>> Spomsors is: %s", sponsors);
    }

    rini_set_value(&config, "SHOW_WINDOW_SPONSORS", 1, "Show sponsors window at initialization");



    if (!rini_save(config, IniFileName.c_str())) {

        if (RayFlux::FileHelper::createDirFromFileIfNotExits(IniFileName.c_str())
            && rini_save(config, IniFileName.c_str())
        ) {
            TraceLog(LOG_INFO, ">>>>>>>>>>>>>>>  IniFile SAVED!");
        } else {
             TraceLog(LOG_WARNING, ">>>>>>>>>>>>>>> Failed to save IniFile");
        }
    }
    // initfs syncing ! RayFlux::FileHelper::syncFS(); //WEB

    rini_unload(&config);

    //------
    app.OnUpdate = [&](F32 dt) {
        Eyes.Update(dt);
        Lights.Update(dt);
    };
    //------
    Vector2 SliderSize = { 100.f, 20.f };

    app.OnRender = [&]() {

        Lights.Render3D();
        Eyes.Render();
        gui.Begin();

        // logo
        if (logoTex) DrawTexture(*logoTex, gui.getX(), gui.getY(), WHITE);
        gui.SameLine(40.f);
        gui.Write("RayFlux Callback Demo", 40, GOLD);
        gui.Write(TextFormat("FPS: %d FT:%f", GetFPS(), GetFrameTime()),20,  RED);

        gui.Write(confPathText.c_str(), 10, ORANGE);
        gui.Write(prefPathText.c_str(), 10, SKYBLUE);
        gui.Write(logoTex ? "Logo loaded" : "Logo failed!", 10);

        gui.CheckBox( defaultGuiSize, "Light Demo enabled", &Lights.isEnabled);
        Lights.RenderGui(gui);

        gui.Separator(100.f);
        if (mainMusic) {
            bool isMusicPlaying = IsMusicStreamPlaying(*mainMusic);
            if (gui.CheckBox(defaultGuiSize, "Music", &isMusicPlaying)) {
                // resume cant be used if not play was called before !
                if (!isMusicPlaying) PauseMusicStream(*mainMusic);
                else ResumeMusicStream(*mainMusic);
            }
        }
        // combine test >>>>>
        gui.setStates(SliderSize);
        if (GuiSlider(gui.mLastBounds, nullptr, "Vol.", &mainMusicVolume, 0.f, 1.f)) {
            SetMusicVolume(*mainMusic,  mainMusicVolume);
        }

        // <<<<

        if (gui.Button(Vector2(100.f, 20.f), "Test Sound" ) == 1) {
            app.playSound("flee.mp3");
        }
        gui.Separator(100.f);
        if (gui.CheckBox(defaultGuiSize, "VSnyc", &app.getSettings()->EnableVSync)) {
            app.getSettings()->setVSync(app.getSettings()->EnableVSync);
        }

        // normalized 25 - 500 fps
        static float fpsLimit = 500.f / (F32)app.getSettings()->getFPSLimit();
        if (gui.Slider(100.f, "FPS Limit", &fpsLimit, 0.05f, 1.f)) {
            app.getSettings()->setFPSLimit((U32)(fpsLimit * 500.f));
        }

        if (gui.CheckBox(defaultGuiSize, "FullScreen", &app.getSettings()->FullScreen)) {
            app.getSettings()->setFullScreen(app.getSettings()->FullScreen);
        }



        gui.End();

    };
    //--------
    app.OnShutDown = [&]() {
       Lights.ShutDown();
       RayFlux::FileHelper::syncFS(); //WEB TEST HERE !
    };
    //--------
    app.Execute();

    return 0;
}
