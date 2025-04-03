#pragma once

#include "Scene.h"
#include "../Game/RoundDataLoader.h"
#include "../ObjectManipulation/TunnelManager.h"
#include "../Objects/Drillku.h"
#include "../Game/CollisionSystem.h"

class BattleScene : public Scene {
    private:
        int roundNum;
        vector<int> roundData;
        Drillku* player;
        Tunnel* currentTunnel = nullptr;
        MovementComp::MOVE_TYPE lastFacing = MovementComp::RIGHT;

        CollisionSystem* colSystem;
        EnemyFactory enemyMaker;
        vector<Enemy*> currentEnemies;

        RoundDataLoader dataLoader;
        TunnelManager* tunManager;

        Vector2i playerPrevTile;
    public:
        BattleScene(string name, int roundNum, Drillku* player);

        void onLoad();
        void onUnload();
        void reloadRoundData();

        void dig();
        void fixTunnel();
        void createTunnel(Tunnel::TunnelType stage);

        void update();
        void draw(RenderWindow* window);

        void setRoundNum(int id);

        // Used to create the starting tunnels that exist to hold enemies
        void initializeTunnel(int x, int y, int enemyType, int type);
};