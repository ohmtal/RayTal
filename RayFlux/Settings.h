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

        std::string Company = "RayLib Test Company";
        std::string Caption = "RayLib Caption";
        std::string Version = "RayLib Test 0.260505";

        //FIXME
        //     // your window icon (have to be .bmp or .png)
        //     std::string IconFilename = "";
        //
        //     //pre path for IconFilename and loadTexture
        //     // base:/ is replaced with your BasePath
        //     // NOTE: add a tralling slash!
        //
        //     std::string AssetPath = "base:/assets/";
        //     std::string SoundPathAppend   = "";
        //     std::string TexturePathAppend = "";
        //
        //     //imgui
        //     bool EnableDockSpace = true;
        //     // pref:/ is replaced with your pref Path
        //     std::string IniFileName = "pref:/appgui.ini";

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

    };

} //namespace
