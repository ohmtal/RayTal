//------------------------------------------------------------------------------
// RayFlux Main
//------------------------------------------------------------------------------
/*
 * [X] OnRender
 * [X] OnShutDown
 * [X] OnUpdate
 * [ ] OnEvent :not really a eventsystem implemented ?! << more research on this
 *
 * [ ] OnUpdate add fixed call with deltaTime
 *
 * [ ] Manager
 *      [ ] BaseManager
 *      [ ] TextureManager
 *      [ ] AudioManager
 *
 * [ ] Like BaseFlux :
 *      [ ] setFullPath
 *      [ ] bool setWindowIcon(SDL_Window* window, std::string fileName);
 *      [X] Init << bool InitSDL();
 *      [ ] bool initImGui();
 *      [ ] void shutDown();
 *      [X] bool Execute();
 *      [ ] void TerminateApplication(void);
 *
 *      //----------------------------------------------------------------------
 *      [ ] bool playSound(std::string fileName, float gain = 1.0f, bool loop = false);
 *      [ ] bool stopSound(std::string fileName  );
 *      [ ] bool renderTexture(std::string fileName , const SDL_FRect *srcrect, const SDL_FRect *dstrect);
 *      [ ] SDL_Texture* getTexture(std::string fileName, bool noAutoLoad = false);
 *
 *
 *
 */

#pragma once

#include "raylib.h"
#include "raymath.h"

#include "TypeDef.h"
#include "Settings.h"

#include <functional>


namespace RayFlux {

    #define COLOR_SLATEGRAY   CLITERAL(Color){ 20, 20, 20, 255 }     // Darkest Gray


    // ---------------- Main Class
    class Main  {
        Settings mSettings;
    public:
        Settings& getSettings() { return mSettings; }
        std::function<void()> OnRender = nullptr;
        std::function<void(const float)> OnUpdate = nullptr;
        // std::function<void(const SDL_Event)> OnEvent = nullptr;
        std::function<void()> OnShutDown = nullptr;

        bool Init();
        void Execute();
    }; //class

} ; //namespace
