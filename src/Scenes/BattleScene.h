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
        int internalTime = 0;
        bool toggleButtonState = false;

        RoundDataLoader dataLoader;
    public:
        /* 
            scene name, number of tunnels, binary array of enemy type in
            each tunnel from left to right top-down where 0 = pookie and
            1 = geygar
        */
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
            
            // PLAYER FROM [GAME]
            addObject(player);
            cout << "[BATTLE SCREEN] Player pushed" << endl;

            cout << "[BATTLE SCREEN] Objects pushed" << endl;
            cout << "Objects: " << getAllObjects().size() << endl;
            /*
                addObject(new Background(""))
            */
        }

        void onUnload() {
            removeAllObjects();
        }

        void reloadRoundData() {
            if (!roundData.empty()) {
                roundData.clear();
            }
            roundData = dataLoader.loadData(roundNum);
        }

        void initializeTunnel(int x, int y, int enemyType, int type) {
            Tunnel* tunnelCap1 = new Tunnel(Tunnel::CAP);
            Tunnel* tunnelCap2 = new Tunnel(Tunnel::CAP);
            Tunnel* tunnelMiddle = new Tunnel(Tunnel::STRAIGHT);

            switch (type) {
                case 0:
                    SpriteManip::turnLeft(tunnelCap1);
                    tunnelCap1->setTileXY(x, y);

                    SpriteManip::turnLeft(tunnelMiddle);
                    tunnelMiddle->setTileXY(x+1, y);

                    SpriteManip::turnRight(tunnelCap2);
                    tunnelCap2->setTileXY(x+3, y-1);
                    break;
                case 1:
                    tunnelCap1->setTileXY(x, y);

                    tunnelMiddle->setTileXY(x, y+1);

                    SpriteManip::turnRight(tunnelCap2);
                    SpriteManip::turnRight(tunnelCap2);
                    tunnelCap2->setTileXY(x+1, y+3);
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