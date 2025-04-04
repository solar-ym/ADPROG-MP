#pragma once

#include "Entity.h"

class Veggie : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
        
        int timer;
        bool isEnabled = false;
    public:
        Veggie();
        Veggie(string textureName);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        void setEnabled(bool enable);
        void setTimer(int newTime);
        
        bool getEnabled();
        int getTimer();
        Sprite* getSprite();
};