#include "AudioManager.h"

AudioManager::AudioManager(){}

//Loads all of the music into the BGM vector
void AudioManager::loadAllMusic(){
    enum MUSIC_ID {MUSIC_START, MUSIC_1to4, MUSIC_5to8, MUSIC_9to12, MUSIC_LOSE, MUSIC_WIN};

    allBGM.push_back(new Music("../../sounds/MUSIC_start.mp3"));
    allBGM.push_back(new Music("../../sounds/MUSIC_1to4.mp3"));
    allBGM.push_back(new Music("../../sounds/MUSIC_5to8.mp3"));
    allBGM.push_back(new Music("../../sounds/MUSIC_9to12.mp3"));
    allBGM.push_back(new Music("../../sounds/MUSIC_lose.mp3"));
    allBGM.push_back(new Music("../../sounds/MUSIC_win.mp3"));

    for(Music* music : allBGM){
        music->setVolume(30);
        music->setLooping(true);
    }
}

//Plays a specific music
void AudioManager::play(MUSIC_ID id){
    allBGM[id]->play();
}

//Stops a specific music
void AudioManager::stop(MUSIC_ID id){
    allBGM[id]->stop();
}

//Stops all music
void AudioManager::stopAll(){
    for(Music* music : allBGM)
        music->stop();
}

//Deconstructor
AudioManager::~AudioManager(){
    for(Music* music : allBGM){
        delete music;
    }

    allBGM.clear();
}