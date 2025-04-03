#include "Tunnel.h"

Tunnel::Tunnel() {}
Tunnel::Tunnel(TunnelType stage) {
    GD_GameResource* res = GD_GameResource::createInstance();
    
    IntRect rect;
    switch (stage) {
        case CAP:
            rect = (*res->getAtlas())["TUNNEL_cap"];
            break;
        case STRAIGHT:
            rect = (*res->getAtlas())["TUNNEL_straight"];
            break;
        case CORNER:
            rect = (*res->getAtlas())["TUNNEL_corner"];
            break;
    }
    
    entSprite = new Sprite(*res->getTexture(),rect);
    entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});

    tunnelType = stage;
}

void Tunnel::changeTunnelType(TunnelType newStage) {
    tunnelType = newStage;
    GD_GameResource* res = GD_GameResource::createInstance();
    
    IntRect rect;
    switch (newStage) {
        case CAP:
            rect = (*res->getAtlas())["TUNNEL_cap"];
            break;
        case STRAIGHT:
            rect = (*res->getAtlas())["TUNNEL_straight"];
            break;
        case CORNER:
            rect = (*res->getAtlas())["TUNNEL_corner"];
            break;
    }

    entSprite->setTextureRect(rect);
}

void Tunnel::extend(MovementComp::MOVE_TYPE isFacing){

    if (entSprite->getTextureRect().size.y < TILE_SIZE) {
        alterTextureRect(IntRect(
            entSprite->getTextureRect().position, 
            {50, entSprite->getTextureRect().size.y + 10}
        ));
    } else {
        maxExtended = true;
    }
}

void Tunnel::maxExtend() {
    if (entSprite->getTextureRect().size.x < TILE_SIZE) {
        alterTextureRect(IntRect(
            entSprite->getTextureRect().position, 
            {50, 50}
        ));
    }
    maxExtended = true;
}

void Tunnel::alterTextureRect(IntRect newRect) {
    entSprite->setTextureRect(newRect); 
}

void Tunnel::setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
}
int Tunnel::getTileX() {
    return x;
}
int Tunnel::getTileY() {
    return y;
}

void Tunnel::initialize() {}
void Tunnel::update() {}
void Tunnel::draw(RenderWindow *window) {
    window->draw(*entSprite);
}
ColliderComp* Tunnel::getColliderComp() { return nullptr; }

Sprite* Tunnel::getSprite() {
    return entSprite;
}
bool Tunnel::isMaxExtended() {
    return maxExtended;
}
Tunnel::TunnelType Tunnel::getTunnelType() {
    return tunnelType;
}
