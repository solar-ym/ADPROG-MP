#pragma once

#include "Entity.h"
#include "../Components/MovementComp.h"

class Tunnel : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
        bool maxExtended = false;
        //                        U, D, L, R
        int adjacencyStatus[4] = {0, 0, 0, 0};
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
            entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
        }

        void changeTunnelType(TunnelType newStage) {
            GD_GameResource* res = GD_GameResource::createInstance();
            
            IntRect rect;
            switch (newStage) {
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

            entSprite->setTextureRect(rect);
        }

        void extend(MovementComp::MOVE_TYPE isFacing){

            if (entSprite->getTextureRect().size.y < TILE_SIZE) {
                alterTextureRect(IntRect(
                    entSprite->getTextureRect().position, 
                    {50, entSprite->getTextureRect().size.y + 10}
                ));
            } else {
                maxExtended = true;
            }
        }

        void maxExtend() {
            if (entSprite->getTextureRect().size.x < TILE_SIZE) {
                alterTextureRect(IntRect(
                    entSprite->getTextureRect().position, 
                    {50, 50}
                ));
            }
            maxExtended = true;
        }

        void alterTextureRect(IntRect newRect) {
            entSprite->setTextureRect(newRect); 
        }

        void setTileXY(int xV, int yV) {
            x = xV; y = yV;
            entSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
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
        bool isMaxExtended() {
            return maxExtended;
        }
};