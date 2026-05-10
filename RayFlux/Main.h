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

#include "TypeDef.h"
#include "Settings.h"
#include "ResourceManager.h"


#include <functional>


namespace RayFlux {

    #define COLOR_SLATEGRAY   CLITERAL(Color){ 20, 20, 20, 255 }     // Darkest Gray


    // ---------------- Main Class
    class Main  {
        Settings mSettings;
        std::unique_ptr<ResourceManager> mResourceManager;
    public:
        Settings* getSettings() { return &mSettings; }
        ResourceManager* getResourceManager() { return mResourceManager.get(); }

        std::function<bool()> OnInit = nullptr;
        std::function<void()> OnRender = nullptr;
        std::function<void(const F32)> OnUpdate = nullptr;
        // std::function<void(const SDL_Event)> OnEvent = nullptr;
        std::function<void()> OnShutDown = nullptr;

        bool Init();
        void Execute();
        void ShutDown();

        /**
         * setFullPath
         * replace a path with full path
         * %base => SDL_GetBasePath
         * %pref => Settings::getPrefsPath
         */
        void setFullPath(std::string& path){ getSettings()->setFullPath(path); }

        bool playMusic(const char * musicFileName, F32 volume = 1.f);
        bool playSound( const char* soundFileName );
        Music* getMusic(const char * musicFileName) { return getResourceManager()->getMusic(musicFileName);}
        Sound* getSound(const char* soundFileName) { return getResourceManager()->getSound(soundFileName); }
        Texture* getTexture(const char* fileName) { return getResourceManager()->getTexture(fileName); }

    }; //class

} ; //namespace
