/*
 * Demo with class
 */

#include "RayFlux/Main.h"
#include "RayFlux/Gui.h"

#include "Eyes.h"
#include "Lights.h"

#include <string>
#include <math.h>
//------------------------------------------------------------------------------
using namespace RayFlux::Tools;

//------------------------------------------------------------------------------
namespace RayFlux {

class DemoMain: public Main {
    typedef Main Parent ;

    Texture2D* logoTex;


    Demo::Lights mLights;
    Demo::Eyes mEyes;

    // GUI
    RayFlux::LazyGui mLazyGui {10, 10, 20};
    std::string mConfPathText = "";
    std::string mPrefPathText = "";

public:
    //----------------------------------------------------------------------
    bool Init() override{

        if (!Parent::Init()) return false;

        // Music
        playMusic("fullhouse2026.fms.mp3", 0.75f);

        // Texture
        logoTex = getResourceManager()->getTexture("raylib_32x32.png");


        mLights.Init();
        mEyes.Init();

        //-------
        mConfPathText = TextFormat("Base Path: %s", getBasePath().c_str());
        mPrefPathText = TextFormat("Config Path: %s", getSettings()->getPrefsPath().c_str());


        return true;
    }
private:
    void ShutDown() override {
        mLights.ShutDown();
        Parent::ShutDown();
    }

    void Update(F32 dt) override {
        Parent::Update(dt);

        mLights.Update(dt);
        mEyes.Update(dt);
    }
    // -------------------------------------------------------------------------
    // this override Render without the Main wrapper Begin/End
    void Render() override{
        BeginDrawing();
        ClearBackground(COLOR_SLATEGRAY);


        mLights.Render3D();
        mEyes.Render();

        mLazyGui.y = 10;

        // logo
        if (logoTex) DrawTexture(*logoTex, mLazyGui.x, mLazyGui.x, WHITE);
        mLazyGui.y += 40.f;
        mLazyGui.size = 40;
        mLazyGui.Write("RayFlux Class Demo", GOLD);
        mLazyGui.size = 20;
        mLazyGui.Write(TextFormat("FPS: %d", GetFPS()),  RED);
        mLazyGui.size = 10;
        mLazyGui.Write(mConfPathText.c_str(), ORANGE);
        mLazyGui.Write(mPrefPathText.c_str(), SKYBLUE);
        mLazyGui.Write(logoTex ? "Logo loaded" : "Logo failed!");
        mLazyGui.size = 20;
        mLazyGui.Write("LIGHTS:", WHITE);
        mLights.RenderGui(mLazyGui);


        if (mLazyGui.Button(100.f, "Test Sound" ) == 1) {
            playSound("flee.mp3");
        }

         EndDrawing();
    }

}; //DEMO
} //namespace
//------------------------------------------------------------------------------

int main(void)
{
    RayFlux::DemoMain app;
    app.getSettings()->WindowMaximized = true;
    app.getSettings()->IconFilename = "texture:/raylib_32x32.png";

    if (!app.Init()) {
        TraceLog(LOG_ERROR, "%s", "Failed to Initialize!");
        return 1;
    }

    app.Execute();

    return 0;
}
