
#include "ResourceManager.h"
#include "Main.h"

namespace RayFlux {

    // -------------------------------------------------------------------------
    // MUSIC need to be called: UpdateMusicStream

    Music* ResourceManager::getMusic(const std::__1::string fileName, bool noAutoLoad) {
        if (isBlackListed(fileName)) return nullptr;

        auto it = mMusicMap.find(fileName);
        if (it != mMusicMap.end()) {
            return &it->second;
        }

        if (noAutoLoad) return nullptr;

        std::string lFileName =  "music:/" + fileName;
        mMain->setFullPath(lFileName);
        Music music = LoadMusicStream(lFileName.c_str());
        if (!IsMusicValid(music)) {
            blacklist(fileName);
            UnloadMusicStream(music);
            return nullptr;
        }
        mMusicMap[fileName] = music;

        return &mMusicMap[fileName];
    }
    // -------------------------------------------------------------------------
    Sound* ResourceManager::getSound(const std::__1::string fileName, bool noAutoLoad) {
        if (isBlackListed(fileName)) return nullptr;


        auto it = mSoundMap.find(fileName);
        if (it != mSoundMap.end()) {
            return &it->second;
        }
        if (noAutoLoad) return nullptr;

        std::string lFileName =  "sound:/" + fileName;
        mMain->setFullPath(lFileName);


        //FIXME
    }
    // -------------------------------------------------------------------------
    Texture2D* ResourceManager::getTexture(const std::__1::string fileName, bool noAutoLoad) {
        if (isBlackListed(fileName)) return nullptr;

        auto it = mTextureMap.find(fileName);
        if (it != mTextureMap.end()) {
            return &it->second;
        }

        if (noAutoLoad) return nullptr;

        std::string lFileName =  "texture:/" + fileName;
        mMain->setFullPath(lFileName);

        //FIXME
    }

}
