#pragma once

#include "Entity.h"

class Tunnel : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
    public:
        enum TunnelType {CAP, STRAIGHT, CORNER};
        Tunnel() {}
        Tunnel(TunnelType stage) {
            GD_GameResource* res = GD_GameResource::createInstance();
            
            IntRect rect;
            switch (stage) {
                case CAP:
                    rect = (*res->getAtlas())["TUNNEL_cap"];
                    break;
                case STRAIGHT:
                    rect = (*res->getAtlas())["TUNNEL_straight"];
                    break;
                case CORNER:
                    rect = (*res->getAtlas())["TUNNEL_corner"];
                    break;
            }
            
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void setTileXY(int xV, int yV) {
            x = xV; y = yV;
            entSprite->setPosition({TILE_SIZE*(x), TILE_SIZE*(y)+(TILE_SIZE*3)});
        }
        int getTileX() {
            return x;
        }
        int getTileY() {
            return y;
        }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }

        Sprite* getSprite() {
            return entSprite;
        }
};