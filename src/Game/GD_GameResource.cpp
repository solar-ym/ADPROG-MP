#include "GD_GameResource.h"

GD_GameResource* GD_GameResource::myInstance = nullptr;

GD_GameResource::GD_GameResource(){
    //Game sprites
    if(texture.loadFromFile("../../sprites/digDrillkuSpritesheet.png")
            && font.openFromFile("../../sprites/GlacialIndifference-Regular.otf") ){
        atlas = createDictionary("../../sprites/digDrillkuSpritesheet.atlas");
	}

    //Screen UI assets
    if(UITexture.loadFromFile("../../sprites/digDrillkuScreenUI.png")
        && font.openFromFile("../../sprites/GlacialIndifference-Regular.otf") ){
        UIAtlas = createDictionary("../../sprites/digDrillkuScreenUI.atlas");
    }
}

GD_GameResource* GD_GameResource::createInstance(){
    if(myInstance == nullptr)
        myInstance = new GD_GameResource();
    return myInstance;
}

unordered_map<string,IntRect>* GD_GameResource::getAtlas(){
    return atlas;
}
unordered_map<string,IntRect>* GD_GameResource::getUIAtlas(){
    return UIAtlas;
}
Texture* GD_GameResource::getTexture(){
    return &texture;
}
Texture* GD_GameResource::getUITexture(){
    return &UITexture;
}
Font* GD_GameResource::getFont(){
    return &font;
}
