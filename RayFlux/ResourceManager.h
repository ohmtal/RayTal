//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// RayFlux ResourceManager
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "raylib.h"

namespace RayFlux {
    class Main; //fwd
    class ResourceManager {
    protected:
        Main* mMain = nullptr;
    private:
        std::vector<std::string> mBlacklist; //blacklisted filename

        std::unordered_map<std::string, Sound> mSoundMap;
        std::unordered_map<std::string, Music> mMusicMap;
        std::unordered_map<std::string, Texture2D> mTextureMap;

        bool mInitialized = false;
        bool mShutDown = false;

    public:
        ResourceManager(Main* main) : mMain(main) {
            if (main) mInitialized = true;
        }

        ~ResourceManager() {
            shutDown();
        }
        //-------------------------------------------------
        bool isBlackListed(std::string fileName) {
            return std::find(mBlacklist.begin(), mBlacklist.end(), fileName) != mBlacklist.end();
        }

        void blacklist(std::string fileName) {
            if (!isBlackListed(fileName))
                mBlacklist.push_back(fileName);
        }
        //-------------------------------------------------
        void shutDown() {
            if (mShutDown) return;
            mShutDown = true;

            for (auto& [key, val] : mSoundMap) {
                UnloadSound(val);
            }

            for (auto& [key, val] : mMusicMap) {
                UnloadMusicStream(val);
            }

            for (auto& [key, val] : mTextureMap) {
                UnloadTexture(val);
            }
        }
        //-------------------------------------------------
        void Update() {

            for (auto& [key, music] : mMusicMap) {
                 UpdateMusicStream( music );
            }

        }
        //-------------------------------------------------
        Music* getMusic(const std::string fileName , bool noAutoLoad = false );
        Sound* getSound(const std::string fileName, bool noAutoLoad = false );
        Texture2D* getTexture(const std::string fileName, bool noAutoLoad = false);

    }; //ResourceManager

}; //namespace
