#pragma once

#include "Scene.h"
#include "../Game/RoundDataLoader.h"
#include "../Objects/enemies/Enemy.h"
#include "../Objects/Tunnel.h"
#include "../Objects/Drillku.h"

class BattleScene : public Scene {
    private:
        int roundNum;
        vector<int> roundData;
         // enum objIndex {BACKGROUND, BUTTON, ARROW};
        Drillku* player;
        Tunnel* currentTunnel = nullptr;
        MovementComp::MOVE_TYPE lastFacing = MovementComp::RIGHT;

        RoundDataLoader dataLoader;
        int status[DIRT_HEIGHT][DIRT_WIDTH] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
    public:
        BattleScene(string name, int roundNum, Drillku* player) : Scene(name) {
            roundData.clear();
            this->roundNum = roundNum;
            this->player = player;
        }

        void onLoad() {
            cout << "Attempting to load Battle Screen" << endl;

            reloadRoundData(); 
            cout << "[BATTLE SCREEN] Round data loaded" << endl;
            cout << "   > roundData size: " << roundData.size() << endl;
            
            Background* bg  = new Background("BG1_norm");
            cout << "[BATTLE SCREEN] Background created" << endl;
            addObject(bg);
            cout << "[BATTLE SCREEN] Background pushed" << endl;

            // TUNNELS
            for (int i = 0; i < roundData.size(); i += 4) {
                initializeTunnel(roundData[i], roundData[i+1], roundData[i+2], roundData[i+3]);
            }

            cout << "[BATTLE SCREEN] Objects pushed" << endl;
            cout << "Objects: " << getAllObjects().size() << endl;
        }

        void onUnload() {
            removeAllObjects();
        }

        void reloadRoundData() {
            if (!roundData.empty()) {
                roundData.clear();
            }

            for (int i = 0; i < DIRT_HEIGHT; i++) {
                for (int j = 0; j < DIRT_WIDTH; j++) {
                    status[i][j] = 0;
                }
            }

            roundData = dataLoader.loadData(roundNum);
        }

        void dig() {
            if (currentTunnel == nullptr && status[player->getTileY()][player->getTileX()] == 0) {
                createTunnel(Tunnel::STRAIGHT);
            } else if (currentTunnel != nullptr) {
                currentTunnel->extend(player->getMoveComp()->isFacing());
            }

            if (currentTunnel != nullptr && currentTunnel->isMaxExtended() &&
                (player->getTileX() != currentTunnel->getTileX() ||
                player->getTileY() != currentTunnel->getTileY())) {  
                    currentTunnel = nullptr;
            }
        }

        void fixTunnel() {
            cout << "[ BATTLE SCENE ] Trying to fix tunnel." << endl;

            currentTunnel->maxExtend();
            currentTunnel->getSprite()->setRotation(degrees(0));

            switch (player->getMoveComp()->isFacing()) {
                case MovementComp::UP:
                    if (lastFacing == MovementComp::LEFT) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                    } else if (lastFacing == MovementComp::RIGHT) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                        SpriteManip::turnLeft(currentTunnel);
                    } else if (lastFacing == MovementComp::DOWN) {
                        currentTunnel->changeTunnelType(Tunnel::CAP);
                        SpriteManip::turnLeft(currentTunnel);
                        SpriteManip::turnLeft(currentTunnel);
                    }
                    break;
                case MovementComp::DOWN:
                    if (lastFacing == MovementComp::LEFT) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                        SpriteManip::turnRight(currentTunnel);
                    } else if (lastFacing == MovementComp::RIGHT) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                        SpriteManip::turnRight(currentTunnel);
                        SpriteManip::turnRight(currentTunnel);
                    } else if (lastFacing == MovementComp::UP) {
                        currentTunnel->changeTunnelType(Tunnel::CAP);
                    }
                    break;
                case MovementComp::LEFT:
                    if (lastFacing == MovementComp::DOWN) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                        SpriteManip::turnLeft(currentTunnel);
                    } else if (lastFacing == MovementComp::RIGHT) {
                        currentTunnel->changeTunnelType(Tunnel::CAP);
                        SpriteManip::turnRight(currentTunnel);
                    } else if (lastFacing == MovementComp::UP) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                        SpriteManip::turnLeft(currentTunnel);
                        SpriteManip::turnLeft(currentTunnel);
                    }
                    break;
                case MovementComp::RIGHT:
                    if (lastFacing == MovementComp::DOWN) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                    } else if (lastFacing == MovementComp::LEFT) {
                        currentTunnel->changeTunnelType(Tunnel::CAP);
                        SpriteManip::turnLeft(currentTunnel);
                    } else if (lastFacing == MovementComp::UP) {
                        currentTunnel->changeTunnelType(Tunnel::CORNER);
                        SpriteManip::turnRight(currentTunnel);
                    }
                    break;
            }
        }

        void createTunnel(Tunnel::TunnelType stage) {
            Tunnel* newTunnel = new Tunnel(stage);
            
            // Makes the new tunnel have no width
            newTunnel->alterTextureRect(IntRect(
                newTunnel->getSprite()->getTextureRect().position,
                {50,0}
            ));
            
            // Putting tunnel in correct position and orientation
            int x = player->getTileX(), 
                y = player->getTileY();
            switch (player->getMoveComp()->isFacing()) {
                case MovementComp::UP:
                    // y -= 1;
                    SpriteManip::turnLeft(newTunnel);
                    SpriteManip::turnLeft(newTunnel);
                    break;
                case MovementComp::DOWN:
                    // y += 1;
                    break;
                case MovementComp::LEFT:
                    // x -= 1;
                    SpriteManip::turnRight(newTunnel);
                    break;
                case MovementComp::RIGHT:
                    // x += 1;
                    SpriteManip::turnLeft(newTunnel);
                    break;
            }
            newTunnel->setTileXY(x,y);
            status[y][x] = 1;

            currentTunnel = newTunnel;
            addObject(newTunnel);
        }

        void update() {
            Scene::update();
            player->update();
            if (lastFacing != player->getMoveComp()->isFacing() && currentTunnel != nullptr) {
                fixTunnel();
            }
            if (player->getMoveComp()->getIsMoving()) {
                dig();
            }
            lastFacing = player->getMoveComp()->isFacing();
        }

        void draw(RenderWindow* window) {
            Scene::draw(window);
            player->draw(window);
        }

        void initializeTunnel(int x, int y, int enemyType, int type) {
            Tunnel* tunnelCap1 = new Tunnel(Tunnel::CAP);
            Tunnel* tunnelCap2 = new Tunnel(Tunnel::CAP);
            Tunnel* tunnelMiddle = new Tunnel(Tunnel::STRAIGHT);

            switch (type) {
                case 0:
                    tunnelCap1->setTileXY(x, y);
                    SpriteManip::turnLeft(tunnelCap1);

                    tunnelMiddle->setTileXY(x+1, y);
                    SpriteManip::turnLeft(tunnelMiddle);

                    tunnelCap2->setTileXY(x+2, y);
                    SpriteManip::turnRight(tunnelCap2);
                    break;
                case 1:
                    tunnelCap1->setTileXY(x, y);

                    tunnelMiddle->setTileXY(x, y+1);

                    tunnelCap2->setTileXY(x, y+2);
                    SpriteManip::turnRight(tunnelCap2);
                    SpriteManip::turnRight(tunnelCap2);
                    break;
                default: 
                    cout << "[ BATTLE SCENE ] Tunnel Creation failed. Invalid tunnel orientation." << endl;
                    cout << "   > Orientation recieved: " << type << endl;
                    break;
            }

            addObject(tunnelCap1);
            addObject(tunnelMiddle);
            addObject(tunnelCap2);

            cout << "[ BATTLE SCENE ] Tunnels pushed." << endl;
        }
};