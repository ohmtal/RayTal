//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//------------------------------------------------------------------------------
// RayFlux Main
//------------------------------------------------------------------------------
/*
 *  I have implemented different ways to use it.
 *  1.) Using the Event Functions
 *  2.) Override the Main Class (caution with Render Wrapper!)
 *  *.) Combine Both
 *  ----
 *  Core Objects:
 *  1.)  Adding Objects based on Core with overide Render/Update/ShutDown
 *  2.)  Using Core Objects because of the interface or call the methods
 *       manually.
 */

// ---------- TODO ---------------
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
 *      [ ] bool setWindowIcon(Image image);
 *          Image myImage = LoadImage("..")
 *          SetWindowIcon(myImage);
 *          UnloadImage(myImage); // in Test it did (desktop source copy the pixels) work but there are different platforms
 *      [X] Init << bool InitSDL();
 *      [~] bool initImGui();
 *      [ ] void shutDown();
 *      [X] bool Execute();
 *      [ ] void TerminateApplication(void);
 *
 *      //----------------------------------------------------------------------
 *      [ ] research how sound objects are handled
 *          NOTE: too bad:  sound and music is handled different ...
 *              => music.looping = true; << use this for one interface !?
 *                 but i guess it's better to handle it different
 *          InitAudioDevice();      // Initialize audio device
 *          Sound fxWav = LoadSound("resources/sound.wav");         // Load WAV audio file
 *          // LoadSoundAlias(Sound source) :: UnloadSoundAlias(Sound alias)
 *          Music music = LoadMusicStream("resources/country.mp3");
 *          ...
 *          SetMusicVolume(music, volume);
 *          SetMusicPan(music, pan);
 *          ...
 *          StopMusicStream(music);
 *          PlayMusicStream(music);
 *          ...
 *          PauseMusicStream(music)
 *          ResumeMusicStream(music);
 *          ...
 *          // normalized value !
 *          timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
 *          if (timePlayed > 1.0f) timePlayed = 1.0f;*
 *          ...
 *          PlaySound(fxWav);
 *          PlayMusicStream(music);
 *          ...
 *          UnloadSound(fxWav);
 *          UnloadMusicStream(music);
 *
 *      [ ] bool playMusic(std::string fileName, F32 gain = 1.0f);
 *      [ ] bool stopMusic(std::string fileName  );
 *      [ ] Music* getMusic(std::string fileName )
 *      [ ] bool playSound(std::string fileName, F32 gain = 1.0f);
 *      [ ] bool stopSound(std::string fileName  );
 *      [ ] Sound* getSound(std::string fileName )
 *      [X] research how textures are handled
 *          Image image = LoadImage("resources/raylib_logo.png");
 *          Texture2D texture = LoadTextureFromImage(image);
 *           UnloadImage(image);
 *           ...
 *           DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
 *           ...
 *            UnloadTexture(texture);
 *      [ ] bool renderTexture(std::string fileName , Rectangle srcrect, Rectangle dstrect, .....);
 *          ==> void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, F32 rotation, Color tint)
 *
 *      [ ] Texture2D* getTexture(std::string fileName, bool noAutoLoad = false);
 *
 *
 *
 */

#pragma once

#include "raylib.h"
#include "raymath.h"

#include "Core.h"
#include "TypeDef.h"
#include "Settings.h"
#include "ResourceManager.h"


#include <functional>


namespace RayFlux {

    #define COLOR_SLATEGRAY   CLITERAL(Color){ 20, 20, 20, 255 }     // Darkest Gray


    // ---------------- Main Class
    class Main :public Core {
    protected:
        Settings mSettings;
        std::unique_ptr<ResourceManager> mResourceManager;

    public:
        /**
         * a list of Objects based on Core
         * automated calls: Render, Update and ShutDown
         * NOTE: untested!
         */
        std::vector<std::unique_ptr<Core>> mCoreObjects;

        Settings* getSettings() { return &mSettings; }
        ResourceManager* getResourceManager() { return mResourceManager.get(); }

        // ---------- Events ----------
        /**
         * Event OnInit - called after base init is done
         */
        std::function<bool()> OnInit = nullptr;
        /**
         * Event OnRender - wrap begin/end drawing and clear
         */
        std::function<void()> OnRender = nullptr;
        /**
         * Event OnUpdate - called at a fixed deltaTime
         */
        std::function<void(const F32)> OnUpdate = nullptr;
        /**
         * Event OnShutDown - called on shutdown system before
         *                    method ShutDown is called.
         */
        std::function<void()> OnShutDown = nullptr;

        // ---------- Methods ----------
        /**
         * Init - create window and apply settings
         */
        bool Init() override;
        /**
         * update call at a fixed delta time (60fps)
         */
        void Update(F32 dt) override;
        /**
         * render call
         */
        void Render() override;
        /**
         * Shutdown - unload objects
         */
        void ShutDown() override;

        /**
         * Main object loop
         */
        void Execute();

        // ---------- Tool Functions ----------
        /**
         * setFullPath
         * replace a path with full path (see also Settings and Tools)
         */
        void setFullPath(std::string& path){ getSettings()->setFullPath(path); }


        // ---------- Resources ----------
        /**
         * using ResourceManager to get resources
         * it's a bit slower than direct loading (map lookup)
         * but more comfortable and garbage collection is automated.
         */
        bool playMusic(const char * musicFileName, F32 volume = 1.f);
        bool playSound( const char* soundFileName );
        Music* getMusic(const char * musicFileName) { return getResourceManager()->getMusic(musicFileName);}
        Sound* getSound(const char* soundFileName) { return getResourceManager()->getSound(soundFileName); }
        Texture* getTexture(const char* fileName) { return getResourceManager()->getTexture(fileName); }

    }; //class

} ; //namespace
