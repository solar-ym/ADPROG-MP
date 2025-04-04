#include "Rock.h"

Rock::Rock(int x, int y, TunnelManager* manager) : Entity("Rock") {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())["ROCK_default"];
    entSprite = new Sprite(*res->getTexture(),rect);

    entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});

    setTileXY(x, y);
    this->manager = manager;
}

void Rock :: fall() {
    if (currentStage == BROKEN)
        isEnabled = false;
    else {
        if (manager->hasTunnel(x, y) && currentStage == PARTIAL)
            changeTexture(BROKEN);
        else if (manager->hasTunnel(x, y) && currentStage == WHOLE)
            changeTexture(PARTIAL);
        else if (!(manager->hasTunnel(x, y)) && currentStage == WHOLE) {
            setTileXY(x, y+1); 
        }
    }
}

void Rock::setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
}
int Rock::getTileX() { return x; }
int Rock::getTileY() { return y; }

void Rock::initialize() {}
void Rock::update() {
    if (manager->hasTunnel(x, y+1) && isRunning == false)
        isRunning = true;
    
    if (internalTime < 500 && isRunning) internalTime++;

    if (internalTime > 200) {
        fall();
        internalTime = 0;
    }

}
void Rock::draw(RenderWindow *window) {
    if (isEnabled)
        window->draw(*entSprite);
}

void Rock::changeTexture(ROCK_STAGE stage) {
    GD_GameResource* res = GD_GameResource::createInstance();

    IntRect rect;
    
    switch (stage) {
        case WHOLE:
            rect = (*res->getAtlas())["ROCK_default"];
            break;
        case PARTIAL:
            rect = (*res->getAtlas())["ROCK_crumble1"];
            break;
        case BROKEN:
            rect = (*res->getAtlas())["ROCK_crumble2"];
            break;
    }

    entSprite->setTextureRect(rect);
    currentStage = stage;
}

Sprite* Rock::getSprite() {
    return entSprite;
}

void Rock::setEnabled(bool value){
    isEnabled = value;
}

bool Rock::getRunning(){ return isRunning; }
