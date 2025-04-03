#include "EntityAttack.h"

EntityAttack::EntityAttack() {}

EntityAttack::EntityAttack(Entity* owner, string textureName) : Entity("Attack") {
    if (attTexture.loadFromFile("../../sprites/" + textureName))
        attackSprite = new Sprite(attTexture);
    
    collision = new ColliderComp(TILE_SIZE);
    collision->attachComponent(this);
}

void EntityAttack::toggleVisibility() {
    isVisible = !isVisible;
}
bool EntityAttack::getVisibility() {
    return isVisible;
}

void EntityAttack::alterTextureRect(IntRect newRect) {
    attackSprite->setTextureRect(newRect); 
}
void EntityAttack::setSpriteRotation(Angle newRotation) {
    attackSprite->setRotation(newRotation);
}
void EntityAttack::setSpritePosition(float x, float y) {
    attackSprite->setPosition({x, y});
}

void EntityAttack::setTileXY(int xV, int yV) {
    x = xV; y = yV;
    attackSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
}
int EntityAttack::getTileX() { 
    x = (attackSprite->getPosition().x / TILE_SIZE);
    return x; 
}
int EntityAttack::getTileY() { 
    y = (attackSprite->getPosition().y / TILE_SIZE) - SKY_HEIGHT;
    return y; 
}

void EntityAttack::initialize() {}
void EntityAttack::update() {} 
void EntityAttack::draw(RenderWindow *window) { 
    window->draw(*attackSprite); 
}

ColliderComp* EntityAttack::getColliderComp() { return collision; }

Sprite* EntityAttack::getSprite() {
    return attackSprite;
}

int EntityAttack::getTextRect_X() {
    return attackSprite->getTextureRect().size.x;
}
int EntityAttack::getTextRect_Y() {
    return attackSprite->getTextureRect().size.y;
}
