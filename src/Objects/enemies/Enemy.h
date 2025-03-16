#pragma once

#include "../Entity.h"
#include "../../Components/Component.h"

class Enemy : public Entity {
    private:
        // components
        vector<Component*> comps;

        Sprite* entSprite;
    public:
        Enemy();
        Enemy(string name, string textureName);

        void addComponent(Component* newComp);

        void initialize();
        void update();
        void draw(RenderWindow *window);
};