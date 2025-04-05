#pragma once

#include "../Utility/configurations.h"

/*
    Audio Manager Class.

    Holds the vector for all of the background music, and an enum to play the corresponding music
    Also stops a specific music or all of them
*/
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