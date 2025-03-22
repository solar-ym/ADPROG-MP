#pragma once

#include "../Entity.h"
#include "../../Components/Component.h"

class Enemy : public Entity {
    private:
        int x;
        int y;
        // components
        vector<Component*> comps;

        Sprite* entSprite;
    public:
        Enemy();
        Enemy(string name, string textureName);

        void addComponent(Component* newComp);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        Sprite* getSprite();
};