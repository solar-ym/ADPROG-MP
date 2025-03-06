#include "Drillku.h"

Drillku :: Drillku() {}

Drillku :: Drillku (string name) : 
            Entity(name) {

    if (entTexture.loadFromFile("../../sprites/attacking.png"))
        entSprite = new Sprite(entTexture);

    if (attTexture.loadFromFile("../../sprites/hairattack.png"))
        attackSprite = new Sprite(attTexture);
    attackSprite->setPosition({entSprite->getPosition().x+50, entSprite->getPosition().y});
    attackSprite->setTextureRect(IntRect({100, 0}, {50,50})); 

    movement = new MovementComp("MovementComp");
    attack = new AttackComp("AttackComp", attackSprite);

    movement->attachComponent(this);
    attack->attachComponent(this);

}

void Drillku :: mikuMove(float x, float y) {
    entSprite->setPosition({x,y});
}

//SETTERS

void Drillku :: setLives(ALTER_LIFE changeType) {
    switch (changeType) {
        case INCREASELIVES: livesLeft++;
            break;
        case DECREASELIVES: livesLeft--;
            break;
        case RESETLIVES: livesLeft = 3;
    }
}

void Drillku :: update(Keyboard::Scan keyCode) {
    if(keyCode == sf::Keyboard::Scan::Z) {
        attack->extend();
    }
        attack->unextend();
}

void Drillku :: draw(RenderWindow *window) {
    window->draw(*entSprite);
    window->draw(*attackSprite);
}