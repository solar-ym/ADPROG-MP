#include "GD_GameResource.h"

GD_GameResource* GD_GameResource::myInstance = nullptr;

GD_GameResource::GD_GameResource(){
    //Game sprites
    if(texture.loadFromFile("../../sprites/digDrillkuSpritesheet.png")
            && font.openFromFile("../../sprites/GlacialIndifference-Regular.otf") ){
        atlas = createDictionary("../../sprites/digDrillkuSpritesheet.atlas");
	}

    //Screen UI assets, part 1 (since the texture packer couldn't fit all the backgrounds)
    if(UITexture1.loadFromFile("../../sprites/digDrillkuScreenUI.png")
        && font.openFromFile("../../sprites/GlacialIndifference-Regular.otf") ){
        UIAtlas1 = createDictionary("../../sprites/digDrillkuScreenUI.atlas");
    }

    //Screen UI, part 2
    if(UITexture2.loadFromFile("../../sprites/digDrillkuGameBGS.png")
        && font.openFromFile("../../sprites/GlacialIndifference-Regular.otf") ){
        UIAtlas2 = createDictionary("../../sprites/digDrillkuGameBGS.atlas");
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
unordered_map<string,IntRect>* GD_GameResource::getUIAtlas1(){
    return UIAtlas1;
}
unordered_map<string,IntRect>* GD_GameResource::getUIAtlas2(){
    return UIAtlas2;
}
Texture* GD_GameResource::getTexture(){
    return &texture;
}
Texture* GD_GameResource::getUITexture1(){
    return &UITexture1;
}
Texture* GD_GameResource::getUITexture2(){
    return &UITexture2;
}
Font* GD_GameResource::getFont(){
    return &font;
}
