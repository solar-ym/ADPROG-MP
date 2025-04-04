#pragma once

#include "Entity.h"
#include "../Components/ColliderComp.h"
#include "../ObjectManipulation/TunnelManager.h"
// #include "../Components/AllComponents.h"

class Rock : public Entity {
    public:
        enum ROCK_STAGE {WHOLE, PARTIAL, BROKEN};
        Rock(int x, int y, TunnelManager* manager);

        void fall();

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        void changeTexture(ROCK_STAGE stage);

        void setEnabled(bool value);
        bool getRunning();

        Sprite* getSprite();
    private:
        int internalTime = 0;
        int x;
        int y;
        Sprite* entSprite;
        TunnelManager* manager;

        bool fallen;
        bool isEnabled = true;
        bool isRunning = false;

        ROCK_STAGE currentStage = WHOLE;
};