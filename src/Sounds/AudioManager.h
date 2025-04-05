#pragma once

#include "../Utility/configurations.h"

class AudioManager {
    private:
        vector<Music*> allBGM;
    public:
        enum MUSIC_ID {MUSIC_START, MUSIC_1to4, MUSIC_5to8, MUSIC_9to12, MUSIC_LOSE, MUSIC_WIN};
        AudioManager();
        
        void loadAllMusic();

        void play(MUSIC_ID id);
        void stop(MUSIC_ID id);
        void stopAll();

        ~AudioManager();
};