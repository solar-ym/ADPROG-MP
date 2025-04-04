#pragma once

#include "../Utility/configurations.h"

class AudioManager {
    private:
        vector<Music> allBGM;
    public:
        AudioManager();
        
        void play(int index);
};