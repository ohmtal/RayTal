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
//------------------------------------------------------------------------------
using namespace RayFlux::Tools;
std::string IniFileName = "pref:/RayFlux.ini";
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
    // RayFlux::LazyGui lg {10.f, 10.f};
    RayFlux::Gui gui(10.f, 10.f);
    Vector2 defaultGuiSize{20.f, 20.f};

    //-------
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
        gui.Write(TextFormat("FPS: %d", GetFPS()),20,  RED);

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
        static float sliderVal = 1.f; //GetMusicVolume(mainMusic);
        if (GuiSlider(gui.mLastBounds, nullptr, "Vol.", &sliderVal, 0.f, 1.f)) {
            SetMusicVolume(*mainMusic,  sliderVal);
        }

        // <<<<

        if (gui.Button(Vector2(100.f, 20.f), "Test Sound" ) == 1) {
            app.playSound("flee.mp3");
        }
        gui.Separator(100.f);
        if (gui.CheckBox(defaultGuiSize, "VSnyc", &app.getSettings()->EnableVSync)) {
            app.getSettings()->setVSync(app.getSettings()->EnableVSync);
        }
        if (gui.CheckBox(defaultGuiSize, "FullScreen", &app.getSettings()->FullScreen)) {
            app.getSettings()->setFullScreen(app.getSettings()->FullScreen);
        }



        gui.End();

    };
    //--------
    app.OnShutDown = [&]() {
       Lights.ShutDown();
    };
    //--------
    app.Execute();

    return 0;
}
