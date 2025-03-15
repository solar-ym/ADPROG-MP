#include "GD_GameResource.h"

GD_GameResource* GD_GameResource::myInstance = nullptr;

GD_GameResource::GD_GameResource(){
    if(texture.loadFromFile("../../sprites/miku_spritesheet.png")
            && font.openFromFile("../../sprites/GlacialIndifference-Regular.otf") ){
        atlas = createDictionary("../../sprites/miku.atlas");
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
Texture* GD_GameResource::getTexture(){
    return &texture;
}
Font* GD_GameResource::getFont(){
    return &font;
}
