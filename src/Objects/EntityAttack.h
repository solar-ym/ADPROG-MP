#pragma once

#include "../Utility/configurations.h"
#include "Entity.h"
#include "../Game/GD_GameResource.h"

class EntityAttack : public Entity {
    private:
        Sprite* attackSprite;
        Texture attTexture;
        bool isVisible = false;
    public:
        EntityAttack() {}
        EntityAttack(Sprite* owner, string textureName) {
            // GD_GameResource* res = GD_GameResource::createInstance();
            // IntRect rect = (*res->getAtlas())[textureName];
            // attackSprite = new Sprite(*res->getTexture(),rect);

            if (attTexture.loadFromFile("../../sprites/" + textureName))
                attackSprite = new Sprite(attTexture);
            
            attackSprite->setPosition({owner->getPosition().x+50, owner->getPosition().y});
        }

        void toggleVisibility() {
            isVisible = !isVisible;
        }
        bool getVisibility() {
            return isVisible;
        }
        void alterTextureRect(IntRect newRect) {
            attackSprite->setTextureRect(newRect); 
        }
        void setSpriteRotation(Angle newRotation) {
            attackSprite->setRotation(newRotation);
        }
        void setSpritePosition(Sprite* owner) {
            attackSprite->setPosition({owner->getPosition().x+50, owner->getPosition().y});
        }

        void initialize() {}
        void update() {} 
        void draw(RenderWindow *window) { 
            window->draw(*attackSprite); 
        }

        int getTextRect_X() {
            return attackSprite->getTextureRect().size.x;
        }
        int getTextRect_Y() {
            return attackSprite->getTextureRect().size.y;
        }
};