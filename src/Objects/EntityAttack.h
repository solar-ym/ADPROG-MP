#pragma once

#include "../Utility/configurations.h"
#include "Entity.h"
#include "../Game/GD_GameResource.h"

class EntityAttack : public Entity {
    private:
        int x;
        int y;
        
        Sprite* attackSprite;
        Texture attTexture;
        bool isVisible = false;
    public:
        EntityAttack() {}
        EntityAttack(Entity* owner, string textureName) {
            if (attTexture.loadFromFile("../../sprites/" + textureName))
                attackSprite = new Sprite(attTexture);
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
        void setSpritePosition(float x, float y) {
            attackSprite->setPosition({x, y});
        }

        void setTileXY(int xV, int yV) {
            x = xV; y = yV;
            attackSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
        }
        int getTileX() { return x; }
        int getTileY() { return y; }

        void initialize() {}
        void update() {} 
        void draw(RenderWindow *window) { 
            window->draw(*attackSprite); 
        }

        Sprite* getSprite() {
            return attackSprite;
        }

        int getTextRect_X() {
            return attackSprite->getTextureRect().size.x;
        }
        int getTextRect_Y() {
            return attackSprite->getTextureRect().size.y;
        }
};