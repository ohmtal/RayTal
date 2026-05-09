//------------------------------------------------------------------------------
// RayFlux Settings
//------------------------------------------------------------------------------
#pragma once

#include <string>
#include "Tools.h"

namespace RayFlux {
    //--------------------------------------------------------------------------
    struct Settings {
        U16 ScreenWidth = 1152;
        U16 ScreenHeight = 648;
        // not the exact fps since i use integer and round it.
        U16  FpsLimit = 0;
        bool FullScreen       = false;
        bool WindowMaximized  = false;
        // you also can set FpsLimit
        bool EnableVSync      = true;
        bool EnableFSAA       = true;

        bool DisableSound     = false;

        std::string Company = "RayLib Test Company";
        std::string Caption = "RayLib Caption";
        std::string Version = "RayLib Test 0.260505";

        // your window icon (have to be RGBA8 )
        std::string IconFilename = "";

        //pre path for IconFilename and loadTexture
        // base:/ is replaced with your BasePath
        // NOTE: add a tralling slash!

        std::string AssetPath = "base:/assets/";
        std::string SoundPathAppend   = "sound/";
        std::string MusicPathAppend   = "music/";
        std::string TexturePathAppend = "texture/";


        // overwrite Window FLAGS:
        int windowFlagsOverwrite = 0;

        //--------------------------------------------------------------------------
        std::string getPrefsPath(){
            static std::string cachedPath = "";
            if (!cachedPath.empty()) return cachedPath;
            cachedPath = Tools::GetPrefPath(getSafeCompany().c_str(), getSafeCaption().c_str());

            return cachedPath;
        }
        //--------------------------------------------------------------------------
        std::string getSafeCompany(){
            return Tools::sanitizeFilenameWithUnderScores(Company);
        }
        //--------------------------------------------------------------------------
        std::string getSafeCaption(){
            return Tools::sanitizeFilenameWithUnderScores(Caption);
        }
        //--------------------------------------------------------------------------
        void setFPSLimit( int Limit) {
            SetTargetFPS(Limit);
            FpsLimit = Limit;
        }
        //--------------------------------------------------------------------------
        /**
         * replace a path with full path
         * %base => SDL_GetBasePath
         * %pref => Settings::getPrefsPath
         */
        void setFullPath(std::string& path){
            if (path.find("assets:/", 0) != std::string::npos) {
                path = Tools::string_replace_all(path, "assets:/", AssetPath);
            }
            if (path.find("sound:/", 0) != std::string::npos) {
                path = Tools::string_replace_all(path, "sound:/", AssetPath + SoundPathAppend);
            }
            if (path.find("music:/", 0) != std::string::npos) {
                path = Tools::string_replace_all(path, "music:/", AssetPath + MusicPathAppend);
            }
            if (path.find("texture:/", 0) != std::string::npos) {
                path = Tools::string_replace_all(path, "texture:/", AssetPath + TexturePathAppend);
            }
            if (path.find("base:/", 0) != std::string::npos) {
                path = Tools::string_replace_all(path, "base:/", Tools::getBasePath());
            }
            if (path.find("pref:/", 0) != std::string::npos) {
                path = Tools::string_replace_all(path, "pref:/", getPrefsPath());
            }
        }

    }; //Settings

} //namespace
