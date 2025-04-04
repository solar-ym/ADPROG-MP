#pragma once

#include "Entity.h"
#include "../Components/ColliderComp.h"

class Veggie : public Entity {
    private:
        int x;
        int y;
        // components
        vector<Component*> comps;
        Sprite* entSprite;
        
        int timer;
        bool isEnabled;
    public:
        Veggie();
        Veggie(string textureName);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        void addComponent(Component* newComp);
        void setEnabled(bool enable);
        void setTimer(int newTime);
        
        bool getEnabled();
        int getTimer();
        ColliderComp* getColliderComp();
        Sprite* getSprite();
};