#pragma once

#include "Entity.h"
#include "../Components/MovementComp.h"

class Tunnel : public Entity {
    public:
        enum TunnelType {CAP = 1, STRAIGHT, CORNER};
        Tunnel();
        Tunnel(TunnelType stage);

        void changeTunnelType(TunnelType newStage);

        void extend(MovementComp::MOVE_TYPE isFacing);

        void maxExtend();

        void alterTextureRect(IntRect newRect);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        ColliderComp* getColliderComp();
        Sprite* getSprite();
        bool isMaxExtended();
        TunnelType getTunnelType();
    private:
        int x;
        int y;
        Sprite* entSprite;
        bool maxExtended = false;
        TunnelType tunnelType;
};